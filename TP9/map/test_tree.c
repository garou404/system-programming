#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "map_tree.h"

// #define RAND_MAX 10
int main(int argc, char** argv) {
    struct map* map = map_init();
    // for (int i = 0; i < 40; i++) {
    //     int rand_key = (rand() % 40)+1;
    //     printf("rand key %d\n", rand_key);
    //     map_put(map, rand_key, &i);
    // }
    for (int i = 1; i < 11; i++) {
        map_put(map, i, &i);
    }
    // printf("tree root key %d left %p right %p\n", map->root->key, map->root->left, map->root->right);
    print_tree(map);
    map_free(map);
    return EXIT_SUCCESS;
}
