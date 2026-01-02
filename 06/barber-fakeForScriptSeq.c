#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if(argc != 4) {
        printf("Not enough paramters: ./program N printLevel P\n");
        printf("printLevel: 0=no, 1=some, 2=verbouse\n");
        return 1;
    }
    
    printf("CORRECT\n");
    return 0;
}
