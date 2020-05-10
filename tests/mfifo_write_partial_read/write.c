#include "../../src/mfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;
    char cs[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    if(argc == 2){
        // Connect to mfifo object
        if((fifo = mfifo_connect(argv[1], 0, 0, 0)) != NULL){
            // Connected to mfifo object
            printf("Connected to mfifo object \033[1;34m%s\033[0m\n", argv[1]);

            // Writing the random number if exists
            if(mfifo_write_partial(fifo, &cs, 10) == 0)
                printf("Process \033[1;34m%d\033[0m wrote all caracters \033[1;34m%s\033[0m\n", getpid(), cs);
            else{
                printf("Error writing to mfifo object \033[1;34m%s\033[0m\n", argv[1]);
                return 1;
            }
        }
        else{
            printf("Could not connect to mfifo object \033[1;34m%s\033[0m\n", argv[1]);
        }
    }
    else{
        printf("Wrong argument count\n");
    }
    return 0;
}