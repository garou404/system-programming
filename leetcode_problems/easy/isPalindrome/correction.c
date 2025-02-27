#include <stdio.h>
#include <stdlib.h>

int isPalindrome(int x) {
    if (x < 0 || (x!=0 && x % 10 == 0)) { return 0; }
    int check = 0;
    while(x > check){
        check = check*10 + x%10;
        x/=10;
    }
    return (x == check || x == check/10);
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
