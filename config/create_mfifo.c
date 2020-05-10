#include "../src/mfile.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;

    if(argc > 2 && argc < 5){
        if(argv[3] != NULL && strcmp(argv[3], "true") == 0)
            // Create a new mfifo object with O_EXCL option
            fifo = mfifo_connect(argv[1], O_CREAT | O_EXCL, 0666, atoi(argv[2]));
        else
            // Create a new mfifo object
            fifo = mfifo_connect(argv[1], O_CREAT, 0666, atoi(argv[2]));
            
        if(fifo == NULL){
            printf("Error, maybe check argument values or Mfifo object \033[1;34m%s\033[0m already exists\n", argv[1]);
        }
        else{
            printf("Mfifo object \033[1;34m%s\033[0m created with capacity \033[1;34m%ld\033[0m\n", argv[1], mfifo_capacity(fifo));
        }
    }
    else{
        printf("Wrong argument count\n");
    }
    return 0;
}