#include "../../src/mfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;
    int thing;

    srandom(getpid());

    if(argc == 2){
        // Connect
        if((fifo = mfifo_connect(argv[1], 0, 0, 0)) != NULL){
            while(1){
                // Generating a random number
                thing = (random() % 100) + 1;

                // Writing the random number if exists
                if(mfifo_write_partial(fifo, &thing, sizeof(int)) == 0)
                    printf("Wrote a thing %d\n", thing);
                else{
                    printf("Error writing\n");
                }
            }
        }
        else
            printf("\033[1;34m %s\033[0m does not exist\n", argv[1]);
    }
    else
        printf("Wrong argument count\n");
    return 0;
}