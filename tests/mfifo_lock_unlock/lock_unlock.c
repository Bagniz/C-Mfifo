#include "../../src/mfile.h"
#include <unistd.h>


int main(int argc, char **argv){
    // Variables
    mfifo *fifo;

    if(argc == 2){
        // Connect
        if((fifo = mfifo_connect(argv[1], 0, 0, 0)) != NULL){
            if(mfifo_lock(fifo) == 0){
                printf("\033[1;34m %d\033[0m starting to wait\n", getpid());
                sleep(10);
                printf("Process number \033[1;34m%d\033[0m\n", getpid());
                mfifo_unlock(fifo);
            }
            else
                printf("Error\n");
        }
        else
            printf("\033[1;34m %s\033[0m does not exist\n", argv[1]);
    }
    else
        printf("Wrong argument count\n");
    return 0;
}