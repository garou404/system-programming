#include <stdio.h>
#include <stdlib.h>


int string_length(const char*string) {
    int length = 1;
    const char *cur_char = string; // const means that the data being pointed to must not be modified through this pointer
    while (*cur_char != '\0') {
        cur_char++;
        length ++;
    }
    return length;
}

void string_cpy(char* dest, const char* src, size_t n) {
    for (int i = 0; i < n; i++) {
        // printf("test");
        printf("%c\n", *(src+i*sizeof(char)));
        printf("%c\n", *(dest+i*sizeof(char)));
        *(dest+i*sizeof(char)) = *(src+i*sizeof(char));
    }
}

int main(int argc, char** argv) {

    char*test_str = "test\0";
    string_length(test_str);

    char*src = "src string\0";
    char*dst = "dst string\0";
    string_cpy(dst, src, 3*sizeof(char));
    printf("\n%s\n", dst);
    return EXIT_SUCCESS;
}
