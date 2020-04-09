#include "mfile.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
    // Variables
    mfifo *fifo;
    if((fifo = mfifo_connect("Salim", 0, 0666, 10)) != NULL){
        srandom(getpid());

        // Write to the fifo object
        for (int i = 0; i < 5; i++){
            int j = (random() % 100) + 1;
            if(mfifo_write(fifo, &j, sizeof(j)) == 0){
                printf("Wrote %d\n", j);
            }
        }
    }
    else{
        printf("sdazd\n");
    }
    return 0;
} 