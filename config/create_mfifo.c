#include "../src/mfile.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;

    if(argc > 2){
        // Create a new mfifo object
        if(argv[3] != NULL && strcmp(argv[3], "true") == 0)
            fifo = mfifo_connect(argv[1], O_CREAT | O_EXCL, 0666, atoi(argv[2]));
        else
            fifo = mfifo_connect(argv[1], O_CREAT, 0666, atoi(argv[2]));
            
        if(fifo == NULL){
            printf("Error, maybe check argument values\n");
        }
        else{
            printf("Mfifo object %s created with capacity %ld\n", argv[1], mfifo_capacity(fifo));
        }
    }
    else{
        printf("Wrong argument count\n");
    }
    return 0;
}