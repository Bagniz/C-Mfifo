#include "../../src/mfile.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;

    if(argc == 3 || argc == 4){
        if(strcmp(argv[1],"anonymous") == 0){
            // Create a new named mfifo object
            fifo = mfifo_connect(NULL, 0, 0, atoi(argv[2]));
                
            if(fifo == NULL)
                printf("Error, maybe check argument values\n");
            else{
                printf("Anonymous mfifo object created with capacity \033[1;34m%ld\033[0m\n", mfifo_capacity(fifo));
            }
        }
        else{
            // Create a new named mfifo object
            if(argv[3] != NULL && strcmp(argv[3], "true") == 0)
                fifo = mfifo_connect(argv[1], O_CREAT | O_EXCL, 0666, atoi(argv[2]));
            else
                fifo = mfifo_connect(argv[1], O_CREAT, 0666, atoi(argv[2]));
                
            if(fifo == NULL)
                printf("Error, maybe check argument values\n");
            else
                printf("Mfifo object \033[1;34m%s\033[0m created with capacity \033[1;34m%ld\033[0m\n", argv[1], mfifo_capacity(fifo));
        }
    }
    else if (argc == 2){
        // Connect to a mfifo object
        fifo = mfifo_connect(argv[1], 0, 0, 0);
        if(fifo == NULL)
            printf("\033[1;34m %s\033[0m does not exist\n", argv[1]);
        else
            printf("Connected to mfifo object \033[1;34m%s\033[0m with capacity \033[1;34m%ld\033[0m\n", argv[1], mfifo_capacity(fifo));
    }
    else
        printf("Wrong argument count\n");
    return 0;
}