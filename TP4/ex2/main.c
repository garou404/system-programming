#include <stdio.h>
#include <stdlib.h>

void squares(int tab[], int size) {
    for (int i = 0; i < size; i++) {
        tab[i] = tab[i]*tab[i];
    }
}


void display(int tab[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d, ", tab[i]);
    }
    printf("\n");
}


void init(int*tab, int size) {
    printf("\n%p, %p\n", tab, &tab);
    printf("%p\n", tab);
    for (int i = 0; i < size; i++) {
        *(tab + i*sizeof(int)) = 0;
    }
}

int main(int argc, char** argv) {
    printf("%lu", sizeof(int));
    int tab1[] = {1, 2, 3, 4};

    display(tab1, 4);
    squares(tab1, 4);
    display(tab1, 4);


    int *tab2 = malloc(sizeof(int)*4);

    printf("%p\n", &tab2);
    printf("init tab2\n\n");
    init(tab2, 4);
    display(tab2, 4);

    init(tab1, 4);
    display(tab1, 4);

    // tab1: 0x7ffd470a86a0, &tab1:0x7ffd470a86a0 the same because print("%p", tab1) becomes print("%p", &tab1) due to implicit transtypage
    // tab2: 0x633e8bd956b0, &tab2: 0x7ffd470a8698 not the same because tab2 is of type int address, so is &tab2
    printf("\ntab1: %p, &tab1:%p\ntab2: %p, &tab2: %p\n", tab1, &tab1, tab2, &tab2);
    // sizeof(tab1) => size of the whole array 4*sizeof(int) = 16
    // sizeof(&tab1) => 8 size of pointer
    // sizeof(*&tab1) => Dereferencing &tab1 gives tab1, which is an array 16
    printf("\ntab1: %lu, &tab1:%lu, *&tab1:%lu\ntab2: %lu, &tab2: %lu, *&tab2:%lu\n", sizeof(tab1), sizeof(&tab1), sizeof(*&tab1), sizeof(tab2), sizeof(&tab2), sizeof(*&tab2));
    
    free(tab2);
    return EXIT_SUCCESS;
}