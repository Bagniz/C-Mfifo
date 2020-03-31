#include "mfile.h"
#include <fcntl.h>

int main(int argc, char **argv){
    mfifo *fifo = mfifo_connect("salim", O_CREAT, 0666, 15);
    printf("%ld\n", mfifo_capacity(fifo));
    printf("%d\n", mfifo_disconnect(fifo));
    mfifo_unlink("salim");
    return 0;
}
