#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "student.h"


int main(int argc, char** argv) {
    if(argc != 4) {
        printf("Usage: ./generate input output grade\n");
        return EXIT_FAILURE;
    }

    FILE* in = fopen(argv[1], "r");
    if (in == NULL){
        printf("fopen %s: %s\n", argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    FILE* out = fopen(argv[2], "w");
    if (out == NULL){
        printf("fopen %s: %s\n", argv[2], strerror(errno));
        return EXIT_FAILURE;
    }

    char buffer[NB_CHAR];

    while (fgets(buffer, NB_CHAR, in) != NULL){
        int grade = atoi(argv[3]);
        struct student stdt = {.rank=grade};
        int i = 0;
        char next_char = buffer[i];
        while (next_char != '\n') {
            stdt.name[i] = buffer[i];
            i++;
            next_char = buffer[i];
        }
        // printf("student name %s, grade %d\n\n", stdt.name, stdt.rank);
        fwrite(&stdt, sizeof(struct student), 1, out);
    }
    return EXIT_SUCCESS;
}


// fgets reads characters from the file until:

// It reads a newline (\n)
// It reaches the maximum number of characters (NB_CHAR - 1)
// It encounters EOF