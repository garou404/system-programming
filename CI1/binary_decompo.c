#include <stdlib.h>
#include <stdio.h>
#include <limits.h>



void int_to_bits(int n) {
    
    unsigned int B = 2147483648;
    
    while (n != 0){
        if ((B & n) != 0) {
            printf("1");
            n = n - B;
        }else{
            printf("0");
        }
        // printf("\n -- debug -- n %d B %d -- debug --\n", n, B);
        B = B >> 1;
    }
    printf("\n");
}

int main(int argc, char** argv) {

    int_to_bits(25547);
    return EXIT_SUCCESS;
}