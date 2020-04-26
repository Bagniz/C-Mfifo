#include "../../src/mfile.h"
#include <errno.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;

    if(argc == 2){
        // Connect
        fifo = mfifo_connect(argv[1], 0, 0, 0);
        if(fifo != NULL){
            printf("Connected to from \033[1;34m%s\033[0m\n", argv[1]);
            printf("\033[1;34m %s\033[0m capacity is %ld\n", argv[1], mfifo_capacity(fifo));
        }

        //Disconnect
        if(mfifo_unlink(argv[1]) == 0){
            printf("Disconnected from \033[1;34m%s\033[0m\n", argv[1]);
            printf("Trying to reconnect to \033[1;34m%s\033[0m\n", argv[1]);
            if(mfifo_connect(argv[1], 0, 0, 0) == NULL)
                printf("Could not reconnect to \033[1;34m%s\033[0m it is now deleted\n", argv[1]);   
            else
                printf("Connecting problem\n");
        }
        else
            if(errno == EINVAL || errno == ENOENT)
                printf("\033[1;34m %s\033[0m does not exist\n",argv[1]);
    }
    else
        printf("Wrong argument count\n");
    return 0;
}