#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    srand(getpid());
    int valeur_a_trouver = rand() % 100;
    int input_nb = 0;
    printf("You have 10 guesses\n");
    for (int i = 0; i < 10; i++){
        printf("Please choose a number between 0 and 99 : ");
        scanf("%d", &input_nb);
        if (valeur_a_trouver == input_nb) {
            printf("You found it, the number was %d\n", valeur_a_trouver);
            return EXIT_SUCCESS;
        }else if (valeur_a_trouver > input_nb)
        {
            printf("Sorry wrong number, HIGHER, try again\n");
        }else
        {
            printf("Sorry wrong number, LOWER, try again\n");
        }
    }
    return EXIT_SUCCESS;
}