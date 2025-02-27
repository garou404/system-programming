#include <stdio.h>
#include <stdlib.h>

int power_ten(int power){
    if(power == 0) {
        return 1;
    }else{
        return 10*power_ten(power-1);
    }
}

int isPalindrome(int x) {
    if(x<0) {
        return 0;
    } else if (x < 10)
    {
        return 1;
    }
    int divisor = 1;
    int count = 0;
    while((x % divisor) != x) {
        divisor = divisor*10;
        count++;
    }
    int a = 0, b = 0;
    for(int i = 0; i < count/2; i++) {
        a = (x % (10*power_ten(i)) - a)/power_ten(i);
        b = x / power_ten(count-i-1) % 10;
        printf("round %d: %d - %d\n", i, a, b);
        if (a != b) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: isPalindrome nb\n");
        return EXIT_FAILURE;
    }
    int x = atoi(argv[1]);
    printf("%d is palindrome? => %d\n", x, isPalindrome(x));
    return EXIT_SUCCESS;
}
