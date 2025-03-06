#ifndef MAP_TREE_H
#define MAP_TREE_H

struct node {
    int key;
    void* val;
    struct node* left;
    struct node* right;
};

/* a hashmap.
 * the exact content of the structure may depend on the implementation
 */
struct map {
    struct node* root;
    int height;
};

/* initialize a hashmap */
struct map* map_init();

/* free a map and all the stored values */
void map_free(struct map* map);

/* insert the couple (key, value) */
void map_put(struct map* map, int key, void* val);

/* return the value associated with key */
void* map_get(struct map* map, int key);

/* insert a node n in the tree */
struct node* insert_node(struct node* tree, struct node* n, int* height);

/* free nodes recursively of the binary tree */
void free_node(struct node* node);

/* print the tree */
void print_tree(struct map* map);

#endif /* MAP_TREE_H */
