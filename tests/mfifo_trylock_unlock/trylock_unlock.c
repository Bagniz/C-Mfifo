#include "../../src/mfile.h"
#include <unistd.h>


int main(int argc, char **argv){
    // Variables
    mfifo *fifo;

    if(argc == 2){
        // Connect to mfifo object
        if((fifo = mfifo_connect(argv[1], 0, 0, 0)) != NULL){
            // Connected to mfifo object
            printf("Connected to mfifo object \033[1;34m%s\033[0m\n", argv[1]);

            if(mfifo_trylock(fifo) == 0){
                // TryLocked the mfifo object
                printf("TryLocked mfifo object \033[1;34m%s\033[0m\n", argv[1]);

                // Do something
                for(int i = 0; i < 5; i++){
                    sleep(1);
                    printf("\033[1;34m%d\033[0m\n",i);
                }

                // Unclock the mfifo object
                if(mfifo_unlock(fifo) == 0){
                    printf("Unlocked mfifo object \033[1;34m%s\033[0m\n", argv[1]);
                }
                else{
                    printf("Error unlocking mfifo object \033[1;34m%s\033[0m\n", argv[1]);
                }
            }
            else{
                printf("Cannot trylock mfifo object \033[1;34m%s\033[0m\n", argv[1]);
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