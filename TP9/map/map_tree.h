#ifndef MAP_TREE_H
#define MAP_TREE_H
#define LEFT 0
#define RIGHT 0

enum color_t { BLACK, RED };


struct node {
    int key;
    void* val;
    enum color_t color;
    struct node* children[2];
    struct node* parent;
};

/* a hashmap.
 * the exact content of the structure may depend on the implementation
 */
struct map {
    struct node* root;
    // int height;
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
void insert_node(struct node* tree, struct node* n, int dir);

/* free nodes recursively of the binary tree */
void free_node(struct node* node);

/* print the tree */
void print_tree(struct map* map);

/* print the nodes recursively */
void print_node(struct node* node, int length, int additional_space);

/* literaly print space " " */
void print_space(int n, int additional_space);

#endif /* MAP_TREE_H */
