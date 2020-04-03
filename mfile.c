#include "mfile.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

// TODO: Implement all the functions
// TODO: Assure Mutual Exclusion

// Used to replace -1 & 0 in the code
#define OP_SUCCEEDED 0
#define OP_FAILED -1

// Initialize the mfifo object values
static void initializeMfifoValues(mfifo *fifo, int capacity){
    fifo->capacity = capacity;
    fifo->start = fifo->finish = 0;
}

mfifo *mfifo_connect(const char *name, int options, mode_t permission, size_t capacity){
    // Variables
    int sharedMfifoObject;
    struct stat mfifoObjectStat;
    mfifo *fifo = NULL;

    /**
     * Convert the value of capacity
     * to know if it's < 0
    */
    ssize_t signedCapacity = capacity;

    // Anonymous mFifo
    if(name == NULL){
        if(signedCapacity > 0){
            // Project an anonymous mmap
            fifo = mmap(NULL, sizeof(mfifo) + (capacity * sizeof(char)), PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANON, -1, 0);
            if(fifo != MAP_FAILED){
                initializeMfifoValues(fifo, capacity);
            }
        }
    }
    // Named mFifo
    else{
        // Connect to existing Mfifo
        if(options == 0){ 
            // Open the existing mfifo object
            sharedMfifoObject = shm_open(name, O_RDWR, 0);
            if(sharedMfifoObject != OP_FAILED){
                // Get the shared object size
                if(fstat(sharedMfifoObject, &mfifoObjectStat) != OP_FAILED){
                    // Project the existing mfifo object
                    fifo = mmap(NULL, mfifoObjectStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMfifoObject, 0);
                }
            }
        }
        else if((options == O_CREAT || options == (O_CREAT | O_EXCL))) {
            if(signedCapacity > 0){
                // Create the mfifo object
                sharedMfifoObject = shm_open(name, options | O_RDWR, permission);
                if(sharedMfifoObject != OP_FAILED){
                    // Resize the shared object
                    if(ftruncate(sharedMfifoObject, sizeof(mfifo) + (capacity * sizeof(char))) != OP_FAILED){
                        // Project the existing mfifo object
                        fifo = mmap(NULL, sizeof(mfifo) + (capacity * sizeof(char)), PROT_READ | PROT_WRITE, MAP_SHARED, sharedMfifoObject, 0);
                        if(fifo != MAP_FAILED){
                            initializeMfifoValues(fifo, capacity);
                        }
                    }
                }
            }
        }
    }
    return fifo;
}

int mfifo_disconnect(mfifo *fifo){
    if(fifo != NULL){
        // Deallocate all the fifo mapping
        if(munmap(fifo, sizeof(mfifo) + (mfifo_capacity(fifo) * sizeof(char))) != OP_FAILED){
            return OP_SUCCEEDED;
        }
    }
    return OP_FAILED;
}

int mfifo_unlink(const char *name){
    // Unlink the sharedMfifoObject
    if(shm_unlink(name) != OP_FAILED){
        return OP_SUCCEEDED;
    }
    return OP_FAILED;
}

int mfifo_write(mfifo *fifo, const void *buffer, size_t length){
    // If there is no free space to write
    if(length > mfifo_capacity(fifo)){
        errno = EMSGSIZE;
        return OP_FAILED;
    }
    
    // Check if there is free space to write
    while(length > mfifo_free_memory(fifo));
        // Condition
    
    // Write into fifo
    if(memmove(fifo->memory, buffer, length) == NULL){
        return OP_FAILED;
    }

    // Update the finish field
    fifo->finish = (fifo->finish + length) % mfifo_capacity(fifo);

    return OP_SUCCEEDED;
}

int mfifo_trywrite(mfifo *fifo, const void *buffer, size_t length){
    // If there is no free space to write
    if(length > mfifo_capacity(fifo)){
        errno = EMSGSIZE;
        return OP_FAILED;
    }
    
    // Check if there is free space to write
    if(length > mfifo_free_memory(fifo)){
        errno = EAGAIN;
        return OP_FAILED;
    }
    
    // Write into fifo
    if(memmove(fifo->memory, buffer, length) == NULL){
        return OP_FAILED;
    }

    // Update the finish field
    fifo->finish = (fifo->finish + length) % mfifo_capacity(fifo);

    return OP_SUCCEEDED;
}

int mfifo_write_partial(mfifo *fifo, const void *buffer, size_t length){
    // Check if fifo capacity is more than 0
    if(mfifo_capacity(fifo) > 0){
        // While we did not write everything
        while(length > 0){
            if(mfifo_free_memory(fifo) > 0){
                // Get the length of the buffer we are going to write
                size_t toWrite = (length > mfifo_free_memory(fifo))? (length - mfifo_free_memory(fifo)) : length;

                // Write into fifo
                if(memmove(fifo->memory, buffer, toWrite) == NULL){
                    return OP_FAILED;
                }
                
                // Update the finish field
                fifo->finish = (fifo->finish + toWrite) % mfifo_capacity(fifo);

                // Decrease the length
                length -= toWrite;
            }
        }

        return OP_SUCCEEDED;
    }
    
    errno = EMSGSIZE;
    return OP_FAILED;
}

ssize_t mfifo_read(mfifo *fifo, void *buffer, size_t length){
    // Variables
    size_t toRead, filledSpace;

    // Is it not empty
    if((filledSpace = mfifo_capacity(fifo) - mfifo_free_memory(fifo)) > 0){
        // Get size to read
        toRead = (length <= filledSpace)? length : filledSpace;

        // Read from fifo
        if(memmove(buffer, &fifo->memory[fifo->start], toRead) == NULL){
            return OP_FAILED;
        }

        // Update the start field
        fifo->start = (fifo->start + toRead) % mfifo_capacity(fifo);

        return toRead;
    }

    return OP_FAILED;
}


int mfifo_lock(mfifo *fifo){
    return 0;
}

int mfifo_unlock(mfifo *fifo){
    return 0;
}

int mfifo_trylock(mfifo *fifo){
    return 0;
}

int mfifo_unlock_all(void){
    return 0;
}

size_t mfifo_capacity(mfifo *fifo){
    if(fifo != NULL){
        return fifo->capacity;
    }

    // Handle the Null pointer
    errno = 1;
    return 0;
}

size_t mfifo_free_memory(mfifo *fifo){
    if(fifo != NULL){
        // Calculate the used memory
        int usedMemory = abs(fifo->finish - fifo->start);

        // Return the free memory
        return abs(mfifo_capacity(fifo) - usedMemory);
    }

    // Handle the Null pointer
    errno = 1;
    return 0;
}
