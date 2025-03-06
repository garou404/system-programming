#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "map_tree.h"

int main(int argc, char** argv) {
    struct map* map = map_init();
    for (int i = 0; i < 10; i++) {
        map_put(map, i, &i);
    }
    printf("height of tree: %d\n", map->height);
    // print_tree(map);
    return EXIT_SUCCESS;
}
