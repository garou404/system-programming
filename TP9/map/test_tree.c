#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "map_tree.h"

// #define RAND_MAX 10
int main(int argc, char** argv) {
    struct map* map = map_init();
    map_put(map, 5, NULL);
    printf("key of root %d\n", map->root->key);
    // map_put(map, 2, NULL);

    // print_tree(map);
    map_free(map);
    return EXIT_SUCCESS;
}
