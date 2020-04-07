// Fixes undefined MAP_ANON
#define _GNU_SOURCE

#include "mfile.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

// Used to replace -1 & 0 in the code
#define OP_SUCCEEDED 0
#define OP_FAILED -1

// Initialize the mutexes
static int initializeMutexes(pthread_mutex_t *mutex){
    // Variables
    int code;
    pthread_mutexattr_t mutexAttr;

    // Initialize the mutexAttr
    if((code = pthread_mutexattr_init(&mutexAttr)) == 0){
        // Set mutexAttr shareability
        if((code = pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED)) == 0){
            // Set mutex type
            if((code = pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_ERRORCHECK)) == 0){
                // Initialize the mutex
                code = pthread_mutex_init(mutex, &mutexAttr);
            }
        }
    }

    return code;
}

// Initialize the conditions
static int initializeConditions(pthread_cond_t *condition){
    // Variables
    int code;
    pthread_condattr_t conditionAttr;

    // Initialize the conditionAttr
    if((code = pthread_condattr_init(&conditionAttr)) == 0){
        // Set the condition shareability
        if((code = pthread_condattr_setpshared(&conditionAttr, PTHREAD_PROCESS_SHARED)) == 0){
            // Initialize the condition
            code = pthread_cond_init(condition, &conditionAttr);
        }
    }

    return code;
}

// Initialize the mfifo object values
static void initializeMfifoValues(mfifo *fifo, int capacity){
    fifo->capacity = capacity;
    fifo->start = fifo->finish = 0;
}

// Initialize the mfifo object
static int initializeMfifo(mfifo *fifo, int capacity){
    int code;

    if((code = initializeMutexes(&fifo->mutexReader)) == 0){
        if((code = initializeMutexes(&fifo->mutexWriter)) == 0){
            if((code = initializeConditions(&fifo->isNotFilled)) == 0){
                if((code = initializeConditions(&fifo->isNotEmpty)) == 0){
                    initializeMfifoValues(fifo, capacity);
                }
            }
        }
    }

    return code;
}

mfifo *mfifo_connect(const char *name, int options, mode_t permission, size_t capacity){
    // Variables
    int sharedMfifoObject;
    struct stat mfifoObjectStat;
    mfifo *fifo = NULL;

    /**
     * Convert the value of capacity
     * to know if it's < 0
     * else if the user enters -1 it
     * will be read as a random positive number
    */
    ssize_t signedCapacity = capacity;

    // Anonymous mFifo
    if(name == NULL){
        if(signedCapacity > 0){
            // Project an anonymous mmap
            fifo = mmap(NULL, sizeof(mfifo) + (capacity * sizeof(char)), PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANON, -1, 0);
            if(fifo != MAP_FAILED){
                // Initialize the mfifo
                int code;
                if((code = initializeMfifo(fifo, capacity)) != 0){
                    errno = code;
                    // Disallocat the projection
                    if(mfifo_disconnect(fifo) == OP_SUCCEEDED){
                        fifo = NULL;
                    }
                }
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
                            // Initialize the mfifo
                            int code;
                            if((code = initializeMfifo(fifo, capacity)) != 0){
                                errno = code;
                                // Disallocat the projection
                                if(mfifo_disconnect(fifo) == OP_SUCCEEDED){
                                    fifo = NULL;
                                }
                            }
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
    if(length <= mfifo_capacity(fifo)){
        // Lock the object
        pthread_mutex_lock(&fifo->mutexWriter);

        // Check if there is free space to write
        while(length > mfifo_free_memory(fifo)){
            // Wait on the condition until a signal
            pthread_cond_wait(&fifo->isNotFilled, &fifo->mutexWriter);
        }

        // Write into fifo
        if(memmove(fifo->memory, buffer, length) != NULL){
            // Update the finish field
            fifo->finish = (fifo->finish + length) % mfifo_capacity(fifo);

            // Unlock the mutex
            pthread_mutex_unlock(&fifo->mutexWriter);

            // Signal readers that want to read
            pthread_cond_signal(&fifo->isNotEmpty);

            return OP_SUCCEEDED;
        }

        // Unlock the mutex
        pthread_mutex_unlock(&fifo->mutexWriter);
    }
    else{
        errno = EMSGSIZE;
    }

    return OP_FAILED;
}

int mfifo_trywrite(mfifo *fifo, const void *buffer, size_t length){
    // Variables
    int code;

    // If there is no free space to write
    if(length <= mfifo_capacity(fifo)){
        // Try to lock on the fifo object
        if((code = pthread_mutex_trylock(&fifo->mutexWriter)) == 0){
            // Check if there is free space to write
            if(length <= mfifo_free_memory(fifo)){
                // Write into fifo
                if(memmove(fifo->memory, buffer, length) != NULL){
                    // Update the finish field
                    fifo->finish = (fifo->finish + length) % mfifo_capacity(fifo);

                    // Unlock the mutex
                    pthread_mutex_unlock(&fifo->mutexWriter);

                    // Signal readers that want to read
                    pthread_cond_signal(&fifo->isNotEmpty);

                    return OP_SUCCEEDED;
                }
            }
            else{
                errno = EAGAIN;
            }
        }
        else{
            errno = code;
        }
    }
    else{
        errno = EMSGSIZE;
    }

    // Unlock the mutex
    pthread_mutex_unlock(&fifo->mutexWriter);
    
    return OP_FAILED;
}

int mfifo_write_partial(mfifo *fifo, const void *buffer, size_t length){
    // Check if fifo capacity is more than 0
    if(mfifo_capacity(fifo) > 0){
        // While we did not write everything
        while(length > 0){
            // Lock the object
            pthread_mutex_lock(&fifo->mutexWriter);
            
            if(mfifo_free_memory(fifo) > 0){
                // Get the length of the buffer we are going to write
                size_t toWrite = (length > mfifo_free_memory(fifo))? (length - mfifo_free_memory(fifo)) : length;

                // Write into fifo
                if(memmove(fifo->memory, buffer, toWrite) == NULL){
                    // Unlock the mutex
                    pthread_mutex_unlock(&fifo->mutexWriter);

                    return OP_FAILED;
                }
                
                // Update the finish field
                fifo->finish = (fifo->finish + toWrite) % mfifo_capacity(fifo);

                // Decrease the length
                length -= toWrite;
            }

            // Unlock the mutex
            pthread_mutex_unlock(&fifo->mutexWriter);

            // Signal readers that want to read
            pthread_cond_signal(&fifo->isNotEmpty);
        }

        return OP_SUCCEEDED;
    }

    errno = EMSGSIZE;
    return OP_FAILED;
}

ssize_t mfifo_read(mfifo *fifo, void *buffer, size_t length){
    // Variables
    size_t toRead, filledSpace;
    int code;

    // Try lock the mutexReader
    if((code = pthread_mutex_lock(&fifo->mutexReader)) == 0){
        // Is it not empty
        while((filledSpace = mfifo_capacity(fifo) - mfifo_free_memory(fifo)) <= 0){
            // Wait until the fifo is filled
            pthread_cond_wait(&fifo->isNotEmpty, &fifo->mutexReader);
        }

        // Get size to read
        toRead = (length <= filledSpace)? length : filledSpace;

        // Read from fifo
        if(memmove(buffer, &fifo->memory[fifo->start], toRead) != NULL){
            // Update the start field
            fifo->start = (fifo->start + toRead) % mfifo_capacity(fifo);

            // Unlock the mutex
            pthread_mutex_unlock(&fifo->mutexReader);

            // Signal writer to write if he want
            pthread_cond_signal(&fifo->isNotFilled);

            return toRead;
        }

        // Unlock the mutex
        pthread_mutex_unlock(&fifo->mutexReader);
    }
    else{
        // Is it not empty
        if((filledSpace = mfifo_capacity(fifo) - mfifo_free_memory(fifo)) > 0){
            // Does mfifo contain at least length characters
            if(filledSpace >= length){
                // Read from fifo
                if(memmove(buffer, &fifo->memory[fifo->start], length) != NULL){
                    // Update the start field
                    fifo->start = (fifo->start + length) % mfifo_capacity(fifo);

                    // Signal writer to write if he want
                    pthread_cond_signal(&fifo->isNotFilled);

                    return length;
                }
            }
        }
    }
    return OP_FAILED;
}


int mfifo_lock(mfifo *fifo){
    if(fifo != NULL){
        int code;

        // Lock the mutexReader
        if((code = pthread_mutex_lock(&fifo->mutexReader)) == 0){
            return OP_SUCCEEDED;
        }

        errno = code;
    }
    return OP_FAILED;
}

int mfifo_unlock(mfifo *fifo){
    if(fifo != NULL){
        int code;

        // Unlock the mutexReader
        if((code = pthread_mutex_unlock(&fifo->mutexReader)) == 0){
            return OP_SUCCEEDED;
        }
        errno = code;
    }
    return OP_FAILED;
}

int mfifo_trylock(mfifo *fifo){
    if(fifo != NULL){
        int code;

        // Try to lock the mutexReader
        if((code = pthread_mutex_trylock(&fifo->mutexReader)) == 0){
            return OP_SUCCEEDED;
        }

        errno = EAGAIN;
    }
    return OP_FAILED;
}

int mfifo_unlock_all(void){
    return 0;
}

size_t mfifo_capacity(mfifo *fifo){
    if(fifo != NULL){
        return fifo->capacity;
    }

    // Handle the Null pointer
    errno = EINVAL;
    return OP_SUCCEEDED;
}

size_t mfifo_free_memory(mfifo *fifo){
    if(fifo != NULL){
        // Calculate the used memory
        int usedMemory = abs(fifo->finish - fifo->start);

        // Return the free memory
        return abs(mfifo_capacity(fifo) - usedMemory);
    }

    // Handle the Null pointer
    errno = EINVAL;
    return OP_SUCCEEDED;
}
