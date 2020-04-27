#include "../../src/mfile.h"
#include <unistd.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;
    int thing;

    if(argc == 2){
        // Connect
        if((fifo = mfifo_connect(argv[1], 0, 0, 0)) != NULL){
            while(1){
                // Read the random number if exists
                if(mfifo_read(fifo, &thing, sizeof(int)) > 0)
                    printf("Read a thing %d\n", thing);
                else{
                    printf("Error reading\n");
                    return 1;
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