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
#include <sys/stat.h>

// Define the new Type "mfifo"
typedef struct {

}mfifo;

// TODO: Describe the functions
mfifo *mfifo_connect(const char *name, int options, mode_t permission, size_t capacity);
int mfifo_disconnect(mfifo *fifo);
int mfifo_unlink(const char *name);
int mfifo_write(mfifo *fifo, const void *buffer, size_t length);
int mfifo_trywrite(mfifo *fifo, const void *buffer, size_t length);
int mfifo_write_partial(mfifo *fifo, const void *buffer, size_t length);
ssize_t mfifo_read(mfifo *fifo, void *buffer, size_t length);
int mfifo_lock(mfifo *fifo);
int mfifo_unlock(mfifo *fifo);
int mfifo_trylock(mfifo *fifo);
size_t mfifo_capacity(mfifo *fifo);
size_t mfifo_free_memory(mfifo *fifo);
int mfifo_unlock_all(void);

#endif