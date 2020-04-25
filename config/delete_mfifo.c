#include "../src/mfile.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc > 1){
            
        if(mfifo_unlink(argv[1]) != 0){
            printf("Error, maybe check argument values\n");
        }
        else{
            printf("Mfifo object %s deleted\n", argv[1]);
        }
    }
    else{
        printf("Wrong argument count\n");
    }
    return 0;
}