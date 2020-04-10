#include "mfile.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
    // Variables
    int buffer;
    mfifo *fifo;
    if((fifo = mfifo_connect("Salim", 0, 0666, 13)) != NULL){
        srandom(getpid());
        // Read from the fifo object
        for (int i = 0; i < 5; i++){
            if(mfifo_read(fifo, &buffer, sizeof(buffer)) > 0){
                printf("Read %d\n", buffer);
            }
        }
    }
    return 0;
}