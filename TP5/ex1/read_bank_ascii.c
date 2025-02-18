#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    FILE*f = fopen("./fichier_ascii.dat.txt", "r");
    char *read_result = malloc(40*sizeof(char));
    while (fgets(read_result, 40, f) != NULL) {
        printf("%s", read_result);
    }
    printf("\n");

    fclose(f);
    free(read_result);
    return EXIT_SUCCESS;
}
