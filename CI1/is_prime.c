#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    printf("Veuillez saisir un nombre\n");
    int input_nb = 0;
    scanf("%d", &input_nb);
    printf("Vous avez saisi : %d\n", input_nb);
    for(int i = input_nb - 1; i > 1; --i) {
        if (input_nb % i == 0) {
            printf("%d isn't a prime number\n", input_nb);
            return EXIT_SUCCESS;
        }
    }
    printf("%d is a prime number\n", input_nb);
    return EXIT_SUCCESS;
}