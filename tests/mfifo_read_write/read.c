#include "../../src/mfile.h"
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;
    int number;

    if(argc == 2 || argc == 3){
        // Connect to mfifo object
        if((fifo = mfifo_connect(argv[1], 0, 0, 0)) != NULL){
            // Connected to mfifo object
            printf("Connected to mfifo object \033[1;34m%s\033[0m\n", argv[1]);

            // Lock mfifo object for reading
            if(argv[2] != NULL && strcmp(argv[2], "true") == 0){
                if(mfifo_lock(fifo) == 0){
                    printf("Locked mfifo object \033[1;34m%s\033[0m\n", argv[1]);
                }
                else{
                    printf("Error locking mfifo object \033[1;34m%s\033[0m\n", argv[1]);
                }
            }

            // Read writring numbers if existed
            for(int i = 0; i < 100; i++){
                if(mfifo_read(fifo, &number, sizeof(number)) > 0){
                    printf("Process \033[1;34m%d\033[0m read number \033[1;34m%d\033[0m\n", getpid(), number);
                }
                else{
                    printf("Error reading from mfifo object \033[1;34m%s\033[0m\n", argv[1]);
                    if(argv[2] == NULL || strcmp(argv[2], "true") != 0){
                        return 1;
                    }
                }
            }

            // Unlock mfifo object
            if(argv[2] != NULL && strcmp(argv[2], "true") == 0){
                if(mfifo_unlock(fifo) == 0){
                    printf("Unlocked mfifo object \033[1;34m%s\033[0m\n", argv[1]);
                }
                else{
                    printf("Error unlocking mfifo object \033[1;34m%s\033[0m\n", argv[1]);
                }
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