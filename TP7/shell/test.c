#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {

    // for (int i = 0; i < 4; i++) {
    //     printf("*(tab+%d) = %d\n", i, *(tab+i));
    // }
    
    // printf("\n");
    // for (int i = 0; i < 4; i++) {
    //     printf("*(tab+%d) = %d\n", i, *(tab+i));
    // }
    int count_to = atoi(argv[1]);
    sleep(count_to);
    printf("end of %d sec\n", count_to);
    return EXIT_SUCCESS;
}
