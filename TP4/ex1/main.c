#include <stdio.h>
#include <stdlib.h>


void squares(int* a, int* b) {
    *a = *a*(*a);
    *b = *b*(*b);
}

int main(char**argv, int argc){
    int a = 4;
    int b = 0;

    printf("variable a with value: %d, at address: %p\n", a, &a);
    printf("variable b with value: %d, at address: %p\n\n", b, &b);
    
    int* pa = &a;
    int* pb = &b;

    printf("variable pa with value: %p, at address: %p\n", pa, &pa);
    printf("variable pb with value: %p, at address: %p\n\n", pb, &pb);

    *pb = 9;

    printf("variable a with value: %d, at address: %p\n", a, &a);
    printf("variable b with value: %d, at address: %p\n\n", b, &b);
    
    squares(pa, pb);

    printf("variable a with value: %d, at address: %p\n", a, &a);
    printf("variable b with value: %d, at address: %p\n", b, &b);

    return EXIT_SUCCESS;
}