#include "mfile.h"
#include <fcntl.h>

int main(int argc, char **argv){
    if(mfifo_connect("Salim", O_CREAT, 0666, 13) != NULL){
        printf("Done\n");
    }
    else{
        printf("Error\n");
    }
    return 0;
}