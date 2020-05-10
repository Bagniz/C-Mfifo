#include "../../src/mfile.h"
#include <errno.h>

int main(int argc, char** argv){
    // Variables
    mfifo* fifo;

    if(argc == 2){
        // Connect to mfifo object
        fifo = mfifo_connect(argv[1], 0, 0, 0);
        
        if(fifo != NULL){
            // Connected to mfifo object
            printf("Connected to mfifo object \033[1;34m%s\033[0m\n", argv[1]);

            // Get mfifo object's free memory
            size_t free = mfifo_free_memory(fifo);
            if(errno == EINVAL){
                printf("\033[1;34m %s\033[0m does not exist\n", argv[1]);
            }
            else{
                printf("\033[1;34m %s\033[0m free space is \033[1;34m%ld\033[0m\n", argv[1], free);
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