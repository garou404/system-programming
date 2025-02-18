#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    FILE*f = fopen("./fichier_binaire.dat", "rb");
    int*buffer = malloc(sizeof(int));
    while(fread(buffer, sizeof(int), 1, f) != 0) {
        printf("%d\n", *buffer);
    }
    fclose(f);
    free(buffer);
    // free(read_result);
    return EXIT_SUCCESS;
}
