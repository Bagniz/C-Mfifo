#include "../../src/mfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;
    int number;
    int counter = 0;

    // Set the seed to procces id
    srandom(getpid());

    if(argc == 2){
        // Connect to mfifo object
        if((fifo = mfifo_connect(argv[1], 0, 0, 0)) != NULL){
            // Connected to mfifo object
            printf("Connected to mfifo object \033[1;34m%s\033[0m\n", argv[1]);

            // Write to mfifo object
            while(counter < 100){
                // Generating a random number
                number = (random() % 100) + 1;

                // Writing the random number if exists
                if(mfifo_trywrite(fifo, &number, sizeof(int)) == 0){
                    printf("%d. Process \033[1;34m%d\033[0m wrote number \033[1;34m%d\033[0m\n", counter, getpid(), number);
                    counter++;
                }
                else{
                    printf("Error writing to mfifo object \033[1;34m%s\033[0m\n", argv[1]);
                }
            }
        }
        else{
            printf("\033[1;34m %s\033[0m does not exist\n", argv[1]);
        }
    }
    else{
        printf("Could not connect to mfifo object \033[1;34m%s\033[0m\n", argv[1]);
    }
    return 0;
}