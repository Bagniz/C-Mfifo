#include "../../src/mfile.h"
#include <errno.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;

    if(argc == 2){
        // Connect
        fifo = mfifo_connect(argv[1], 0, 0, 0);
        if(fifo != NULL){
            printf("Connected to from \033[1;34m %s \033[0m\n", argv[1]);
            printf("\033[1;34m %s \033[0m capacity is %ld\n", argv[1], mfifo_capacity(fifo));
        }

        //Disconnect
        if(mfifo_disconnect(fifo) == 0){
            printf("Disconnected from \033[1;34m %s \033[0m\n", argv[1]);
            printf("\033[1;34m %s \033[0m capacity is %ld\n", argv[1], mfifo_capacity(fifo));
        }
        else
            if(errno == EINVAL)
                printf("\033[1;34m %s \033[0m does not exist\n",argv[1]);
            else
                printf("Error\n");
        
    }
    else
        printf("Wrong argument count\n");
    return 0;
}