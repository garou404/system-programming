#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        *(dest + i) = *(src+i);
    }
}

void string_concatenate(char* dest, const char* src, size_t n) {
    char*cur_char = dest;
    int test = 0;
    while(*cur_char != '\0'){
        cur_char++;
        test++;
    }
    for (int i = 0; i < n; i++) {
        *cur_char = *(src+i);
        cur_char++;
    }
    *cur_char = '\0';
}


int main(int argc, char** argv) {

    char*test_str = "test\0";
    string_length(test_str);

    const char *src = "Hello";
    char *dest = malloc(6);
    // char *dest1 = "testest"; //is a string literal, which is stored in read-only memory (usually in the .rodata section of the program).
    string_cpy(dest, src, 3*sizeof(char));
    free(dest);

    char src1[50], dest1[50];
    strcpy(src1, "à tous !");
    strcpy(dest1,  "Bonjour");
    string_concatenate(dest1, src1, 15);
    printf("Final destination string : |%s|\n", dest1);

    return EXIT_SUCCESS;
}

// Declaration	            Writable?  	 Why?
// char *s = "hello";	    ❌ No	    Stored in read-only memory
// char s[] = "hello";	    ✅ Yes	    Stored in stack (modifiable)
// char *s = malloc(6);	    ✅ Yes	    Stored in heap (modifiable)