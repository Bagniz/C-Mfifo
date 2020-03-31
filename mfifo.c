#include "mfile.h"
#include <fcntl.h>

int main(int argc, char **argv){
    mfifo *fifo = mfifo_connect("salim", O_CREAT, 0666, 32);
    int i = 127;
    if(mfifo_write(fifo, &i, sizeof(i)) != -1)
        for (size_t i = 0; i < mfifo_capacity(fifo); i++){
            if(fifo->memory[i] != 0)
                printf("%d number %ld\n", fifo->memory[i], i);
        }
    printf("Finished: %ld\n", fifo->finish);
        
    return 0;
}
