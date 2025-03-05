#ifndef MAP_H
#define MAP_H

struct couple{
    int key;
    void* value;
};
/* a hashmap.
 * the exact content of the structure may depend on the implementation
 */
struct map {
    struct couple* values;
    int nb_element;
};

/* initialize a hashmap */
struct map* map_init();

/* free a map and all the stored values */
void map_free(struct map* map);

/* insert the couple (key, value) */
void map_put(struct map* map, int key, void* val);

/* return the value associated with key */
void* map_get(struct map* map, int key);

#endif /* MAP_H */
