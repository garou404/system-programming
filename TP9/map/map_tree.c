#include <stdio.h>
#include <stdlib.h>
#include "map_tree.h"

struct map* map_init(){
    struct map* my_map = malloc(sizeof(struct map));
    my_map->root = NULL;
    return my_map;
}

void map_free(struct map* map){
    if(map->root) {
        free_node(map->root);
    }
}


void free_node(struct node* node) {
    if(node->children[LEFT]) { free_node(node->children[LEFT]); }
    if(node->children[RIGHT]) { free_node(node->children[RIGHT]); }
    free(node);
}

int child_dir(struct node*p){
    printf("child dir\n");
    if(p->parent->children[LEFT]){
        if(p->parent->children[LEFT] == p){
            return LEFT;
        }else{
            return RIGHT;
        }   
    }else{
        if(p->parent->children[RIGHT] == p){
            return RIGHT;
        }
    }
    return 0;
}

struct node* rotate_dir_root(struct map* rb_tree, struct node* p, int dir) {
    struct node*g = p->parent;
    struct node*s = p->children[1-dir];
    struct node*c;
    c = s->children[dir];
    p->children[dir-1] = c; if (c != NULL) c->parent = p;
    s->children[dir] = p;
    p->parent = s;
    s->parent = g;
    if(g != NULL) {
        g->children[p == g->children[LEFT] ? LEFT : RIGHT] = s;
    }else{
        rb_tree->root = s;
    }
    return s;
}


void insert_node(struct map* rb_tree, struct node* p, struct node* n, int dir) {
    struct node* g; 
    struct node* u;
    n->color = RED;
    n->parent = p;
    if (p == NULL){
        printf("root is NULL\n");
        rb_tree->root = n;
        return;
    }
    p->children[dir] = n;
    do{
        if(p->color == BLACK){
            printf("case I1\n");
            return; // case I1
        }
        if((g = p->parent) == NULL) { // p is root
            p->color = BLACK;
            printf("case I4\n");
            return; // case I4
        }
        // p is red and g is not NULL 
        dir = child_dir(p);
        u = g->children[1-dir];
        if(u == NULL || u->color == BLACK){ // p is red, u is black
            if(n == p->children[1-dir]){ // n is an inner child
                // case I5
                printf("case I5\n");
                rotate_dir(p, dir);
                n = p;
                p = g->children[dir];
            }
            // case I6
            printf("case I6\n");
            printf("rotate_dir_root\n");
            rotate_dir_root(rb_tree, g, 1-dir);
            p->color = BLACK;
            g->color = RED;
            return;
        }

        // case I2: u and p are red
        printf("case I2\n");

        p->color = BLACK;
        u->color = BLACK;
        g->color = RED;
        n = g;
        // new iteration if parent of n not NULL
    }while((p = n->parent) != NULL);
    printf("case I3\n");

    // case I3
}

void find_insertion_node(struct map* rb_tree, struct node* n){
    
    struct node* p = rb_tree->root;
    int dir = 0;
    if(p){
        if(n->key < p->key) { dir = LEFT; }
        else if (p->key < n->key) { dir = RIGHT; }
        else{
            p->val = n->val;
            return;
        }
        while(p->children[dir] != NULL) {
            p = p->children[dir];
            if(n->key < p->key) {
                dir = LEFT;
            }else if (p->key < n->key) {
                dir = RIGHT;
            }else{
                p->val = n->val;
                return;
            }
        }
    }
    printf("insert_node(dir %d)\n", dir);
    insert_node(rb_tree, p, n, dir);
}

void map_put(struct map* rb_tree, int key, void* val){
    struct node* n = malloc(sizeof(struct node));
    n->key = key;
    n->val = val;
    n->children[RIGHT] = NULL;
    n->children[LEFT] = NULL;
    find_insertion_node(rb_tree, n);
}

void* map_get(struct map* map, int key){

    struct node* cur = map->root;
    if(cur) {
        // struct node* next;
        do{
            if((*cur).key == key) {
                return (*cur).val;
            }else if((*cur).key < key){
                cur = (*cur).children[RIGHT];
            }else{
                cur = (*cur).children[LEFT];
            }
        }while(cur != NULL);
    }
    return NULL;
}

void print_tree(struct map* map) {
    if(map->root) {
        print_node(map->root, 0, 0);
        printf("\n");
    }
}

void print_space(int n, int additional_space) {
    for (int i = 0; i < 8*n+additional_space; i++) {
        printf(" ");
    }
}

void print_node(struct node* node, int length, int additional_space) {
    if(node->children[RIGHT] == NULL && node->children[RIGHT] == NULL) {
        char* color = "   ";
        if(node->color == RED) color = "red";
        else color = "bla";
        printf("%d-%s", node->key, color);
        printf("\n");
    }
    if(node->children[RIGHT]){
        char* color = "   ";
        if(node->color == RED) color = "red";
        else color = "bla";
        printf("%d-%s r:", node->key, color);
        // free(color);
        if (node->key > 9){
            print_node(node->children[RIGHT], length+1, additional_space+1);
        }else{
            print_node(node->children[RIGHT], length+1, additional_space);
        }
    }
    if(node->children[LEFT]){
        print_space(length, additional_space);
        char* color = "   ";
        if(node->color == RED) color = "red";
        else color = "bla";
        printf("%d-%s l:", node->key, color);
        if (node->key > 9){
            print_node(node->children[LEFT], length+1, additional_space+1);
        }else{
            print_node(node->children[LEFT], length+1, additional_space);
        }
        return;
    }
}

// [0]________[1]_[2]_[3]___[1]
//    \_______  \_[3]_    \_[2]
//       \__  \_      \_
//          \_