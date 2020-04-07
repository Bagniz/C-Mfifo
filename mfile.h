/**
 * Not defining the header file multiple times
 * if the header file is inluded multiple times.
*/
#ifndef MFILE_HEAD
#define MFILE_HEAD

/**
 * Include needed headers
*/
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>

// Define the new Type "mfifo"
typedef struct {
    size_t capacity;
    size_t start;
    size_t finish;
    pthread_mutex_t mutexReader;
    pthread_mutex_t mutexWriter;
    pthread_cond_t isNotFilled;
    pthread_cond_t isNotEmpty;
    char memory[];
} mfifo;

/**
 * Connects or creats an anonymous or named
 * fifo object and connects to it
*/
mfifo *mfifo_connect(const char *name, int options, mode_t permission, size_t capacity);

/**
 * Disconnect from a fifo object
*/
int mfifo_disconnect(mfifo *fifo);

/**
 * Unlink the fifo object with the name
 * @name, this means delete the object
*/
int mfifo_unlink(const char *name);

/**
 * A synchrones function to write into a fifo object
*/
int mfifo_write(mfifo *fifo, const void *buffer, size_t length);

/**
 * An asynchronous function to write into a fifo object
*/
int mfifo_trywrite(mfifo *fifo, const void *buffer, size_t length);

/**
 * A synchronous function to write into a fifo object
 * that writes all the length from the buffer
*/
int mfifo_write_partial(mfifo *fifo, const void *buffer, size_t length);

/**
 * Allows a process to read form a fifo object
*/
ssize_t mfifo_read(mfifo *fifo, void *buffer, size_t length);

/**
 * A synchronous function to lock
 * the fifo object for reading 
*/
int mfifo_lock(mfifo *fifo);

/**
 * A function to unlock a fifo object 
*/
int mfifo_unlock(mfifo *fifo);

/**
 * An asynchronous function to lock
 * the fifo object for reading 
*/
int mfifo_trylock(mfifo *fifo);

/**
 * A function to unlock all locked
 * fifo objects by a process
*/
int mfifo_unlock_all(void);

/**
 * Returns the capacity of the fifo
 * object passed as a param
*/
size_t mfifo_capacity(mfifo *fifo);

/**
 * Retruns the free available space
 * of the fifo object passed as a param
*/
size_t mfifo_free_memory(mfifo *fifo);

#endif