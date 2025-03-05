#include <stdio.h>
#include <stdlib.h>
#include "map.h"

struct map* map_init(){
    struct map* my_map = malloc(sizeof(struct map));
    my_map->nb_element = 0;
    my_map->values = NULL;
    return my_map;
}

void map_free(struct map* map){
    free(map->values);
    free(map);
}

void map_put(struct map* map, int key, void* val){
    for (int i = 0; i < map->nb_element; i++) { // check if the key is already in the map
        if(map->values[i].key == key) {
            map->values[i].value = val;
            return;
        }
    }
    // if not create new and append to the map
    struct couple new_couple = { .key = key, .value = val };
    (*map).nb_element++;
    map->values = realloc(map->values, sizeof(struct couple)*map->nb_element);
    map->values[map->nb_element-1] = new_couple;
}

void* map_get(struct map* map, int key){
    for (int i = 0; i < map->nb_element; i++) {
        if(map->values[i].key == key){
            return map->values[i].value;
        }
    }
    return NULL;
}
