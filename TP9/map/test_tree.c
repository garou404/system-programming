#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "map_tree.h"

// #define RAND_MAX 10
int main(int argc, char** argv) {
    struct map* rb_tree = map_init();
    // srand(NULL);
    for (int i = 0; i < 10; i++)
    {
        int new_key = rand() % 20;
        printf("MAP_PUT(%d)\n", new_key);
        map_put(rb_tree, new_key, NULL);
        print_tree(rb_tree);
        if(i == 2) break;
    }
    printf("something\n");
    map_free(rb_tree);
    return EXIT_SUCCESS;
}
