#include "mfile.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
    // Variables
    int buffer[10];
    mfifo *fifo;
    if((fifo = mfifo_connect("Salim", 0, 0666, 10)) != NULL){
        srandom(getpid());
        printf("%ld\n", mfifo_capacity(fifo));
        // Read from the fifo object
        for (int i = 0; i < 5; i++){
            if(mfifo_read(fifo, &buffer[i], sizeof(int)) > 0){
                printf("Read %d\n",buffer[i]);
            }
        }
        printf("%ld\n", mfifo_free_memory(fifo));
    }
    return 0;
}