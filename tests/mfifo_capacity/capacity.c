#include "../../src/mfile.h"
#include <errno.h>

int main(int argc, char** argv){
    // Variables
    mfifo* fifo;

    // Connect
    if(argc == 2){
        if(argv[1] != NULL){
            fifo = mfifo_connect(argv[1], 0, 0, 0);
            size_t free = mfifo_capacity(fifo);
            if(errno == EINVAL)
                printf("\033[1;34m %s \033[0m does not exist\n", argv[1]);
            else
                printf("\033[1;34m %s \033[0m capacity is %ld\n", argv[1], free);
        }
    }
    else
        printf("Wrong argument count\n");
    return 0;
}