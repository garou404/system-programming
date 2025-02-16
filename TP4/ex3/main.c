#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

int main(int argc, char** argv) {
    int sum = 0;
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] is at %p: %s\n", i, &argv[i], argv[i]);
        if(i != 0) {
            sum += atoi(argv[i]);
        }
    }
    printf("Sum: %d\n", sum);
    return EXIT_SUCCESS;
}