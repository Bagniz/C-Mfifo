/**
 * Not defining the header file multiple times
 * if the header file is included multiple times.
*/
#ifndef MFILE_HEAD
#define MFILE_HEAD

/**
 * Include needed headers
*/
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>

// mfifo data structure
typedef struct fifoType mfifo;

/**
 * Connects or creats an anonymous or named
 * mfifo object and connects to it.
 * Returns a pointer to mfifo shared object if successful,
 * NULL for errors (Sets errno)
*/
mfifo *mfifo_connect(const char *name, int options, mode_t permission, size_t capacity);

/**
 * Disconnect from mfifo objects.
 * Returns 0 if successful, -1 for errors (Sets errno)
*/
int mfifo_disconnect(mfifo *fifo);

/**
 * Unlink the mfifo object with the name
 * @name, this means delete the object.
 * Returns 0 if successful, -1 for errors (Sets errno)
*/
int mfifo_unlink(const char *name);

/**
 * A synchrones function to write into mfifo objects.
 * Returns 0 if successful, -1 for errors (Sets errno)
*/
int mfifo_write(mfifo *fifo, const void *buffer, size_t length);

/**
 * An asynchronous function to write into mfifo objects.
 * Returns 0 if successful, -1 for errors (Sets errno)
*/
int mfifo_trywrite(mfifo *fifo, const void *buffer, size_t length);

/**
 * A synchronous function to write into mfifo objects
 * that writes all the length from the buffer.
 * Returns 0 if successful, -1 for errors (Sets errno)
*/
int mfifo_write_partial(mfifo *fifo, const void *buffer, size_t length);

/**
 * Allows a process to read form mfifo objects.
 * Returns length read if successful, -1 for errors (Sets errno)
*/
ssize_t mfifo_read(mfifo *fifo, void *buffer, size_t length);

/**
 * A synchronous function to lock
 * mfifo objects for reading.
 * Returns 0 if successful, -1 for errors (Sets errno)
*/
int mfifo_lock(mfifo *fifo);

/**
 * A function to unlock mfifo objects.
 * Returns 0 if successful, -1 for errors (Sets errno)
*/
int mfifo_unlock(mfifo *fifo);

/**
 * An asynchronous function to lock
 * mfifo objects for reading.
 * Returns 0 if successful, -1 for errors (Sets errno)
*/
int mfifo_trylock(mfifo *fifo);

/**
 * A function to unlock all locked
 * mfifo objects by a process
*/
int mfifo_unlock_all(void);

/**
 * Returns the capacity of mfifo
 * objects passed as a param.
 * Returns capacity if successful, 0 for empty errors (Sets errno)
*/
size_t mfifo_capacity(mfifo *fifo);

/**
 * Retruns the free available space
 * of mfifo objects passed as a param.
 * Returns free memory if successful, 0 for full or errors (Sets errno)
*/
size_t mfifo_free_memory(mfifo *fifo);

#endif