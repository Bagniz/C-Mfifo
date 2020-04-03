#include "mfile.h"
#include <fcntl.h>

int main(int argc, char **argv){
    mfifo *fifo = mfifo_connect("salim", O_CREAT, 0666, 32);
    int i = 51;
    char readed[50];
    if(mfifo_write(fifo, &i, sizeof(i)) != -1){
        printf("I: %d\n", i);
        ssize_t count = mfifo_read(fifo, readed, 50);
        printf("Count: %ld\n", count);
        printf("Read: %d\n", readed[0]);
    }
    
    return 0;
}
