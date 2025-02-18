#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>





void encode(uint8_t key, FILE*in, FILE*out) {
    char* read_char = malloc(sizeof(char));
    while(fread(read_char, sizeof(char), 1, in) != 0) {
        printf("%c", *read_char);
        
    }
    free(read_char);
}

void print_bits_of_char(const char c) {
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (c >> i) & 1);
    }
    printf("\n");
}

void print_dec_from_char(const char c){
    printf("%c: ", c);
    for (int i = 7; i >= 0; i--)
    {
        printf("%d*%d", (c >> i) & 1, 128 >> (7-i));
        if (i != 0) {
            printf(" + ");
        }
    }
    printf(" = %d\n", c);
}

void print_bits_of_int(const unsigned int my_int) {
    printf("%d: ", my_int);
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (my_int >> i) & 1);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: ./encode key in out\n");
        return EXIT_FAILURE;
    }
    uint8_t key = atoi(argv[1]);
    printf("encode %s with the key %d to %s\n", argv[2], key, argv[3]);

    FILE* in = fopen(argv[2], "r");
    if (in == NULL) {
        printf("fopen %s: %s\n", argv[2], strerror(errno));
        return EXIT_FAILURE;
    }

    FILE* out = fopen(argv[3], "w");
    if (out == NULL) {
        printf("fopen %s: %s\n", argv[3], strerror(errno));
        return EXIT_FAILURE;
    }

    encode(key, in, out);

    return EXIT_SUCCESS;
}
