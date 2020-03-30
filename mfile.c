#include "mfile.h"
#include <stdlib.h>
#include <errno.h>

// TODO: Implement all the functions

mfifo *mfifo_connect(const char *name, int options, mode_t permission, size_t capacity){
    return 0;
}

int mfifo_disconnect(mfifo *fifo){
    return 0;
}

int mfifo_unlink(const char *name){
    return 0;
}

int mfifo_write(mfifo *fifo, const void *buffer, size_t length){
    return 0;
}

int mfifo_trywrite(mfifo *fifo, const void *buffer, size_t length){
    return 0;
}

int mfifo_write_partial(mfifo *fifo, const void *buffer, size_t length){
    return 0;
}

ssize_t mfifo_read(mfifo *fifo, void *buffer, size_t length){
    return 0;
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

size_t mfifo_capacity(mfifo *fifo){
    return 0;
}

size_t mfifo_free_memory(mfifo *fifo){
    if(fifo != NULL){
        // Calculate the used memory
        int usedMemory = abs(fifo->finish - fifo->start);

        // Return the free memory
        return abs(mfifo_capacity(fifo) - usedMemory);
    }
    else{
        // Handle the Null pointer
        errno = 1;
        perror("Null argument pointer mfifo_free_memory");
        exit(EXIT_FAILURE);
    }
}

int mfifo_unlock_all(void){
    return 0;
}
