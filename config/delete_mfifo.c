#include "../src/mfile.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc == 2){
        // Delete the mfifo object
        if(mfifo_unlink(argv[1]) != 0){
            printf("Error, maybe check argument values or Mfifo object \033[1;34m%s\033[0m does not exist\n", argv[1]);
        }
        else{
            printf("Mfifo object \033[1;34m%s\033[0m deleted\n", argv[1]);
        }
    }
    else{
        printf("Wrong argument count\n");
    }
    return 0;
}