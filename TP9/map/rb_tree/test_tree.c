#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "map_tree.h"

int main(int argc, char** argv) {
    struct map* rb_tree = map_init();
    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        int new_key = rand() % 20;
        map_put(rb_tree, new_key, NULL);
        print_tree(rb_tree);
    }
    map_free(rb_tree);
    return EXIT_SUCCESS;
}
