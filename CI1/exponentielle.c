#include <stdlib.h>
#include <stdio.h>



long facto(int n){
    if (n == 0) {
        return 1;
    }else {
        return n * facto(n-1);
    }
}

double power(double x, int n) {
    if (n != 0) {
        return x * power(x, n-1);
    }else{
        return 1;
    }
}

double expon(double x, int n){
    if (n == 0) {
        return 1;
    }else
    {
        return power(x, n)/facto(n) + expon(x, n-1);
    }
    
}

int main(int argc, char** argv) {
    printf("Please choose a number\n");
    double input_nb = 0;
    scanf("%le", &input_nb);
    double result = expon(input_nb, 20);
    printf("%e\n", result);
    return EXIT_SUCCESS;
}