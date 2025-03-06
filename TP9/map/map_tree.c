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


void insert_node(struct node* tree, struct node* n, int dir) {
    //if tree null => tree = n
    // parent
    // new_child
}


void map_put(struct map* map, int key, void* val){
    struct node* new_node = malloc(sizeof(struct node));
    new_node->key = key;
    new_node->val = val;
    new_node->children[RIGHT] = NULL;
    new_node->children[LEFT] = NULL;
    
    insert_node(map->root, new_node, LEFT);
    

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
    for (int i = 0; i < 4*n+additional_space; i++) {
        printf(" ");
    }
}

void print_node(struct node* node, int length, int additional_space) {
    if(node->children[RIGHT] == NULL && node->children[RIGHT] == NULL) {
        printf("%d", node->key);
        printf("\n");
    }
    if(node->children[RIGHT]){
        printf("%d r:", node->key);
        if (node->key > 9){
            print_node(node->children[RIGHT], length+1, additional_space+1);
        }else{
            print_node(node->children[RIGHT], length+1, additional_space);
        }
    }
    if(node->children[LEFT]){
        print_space(length, additional_space);
        printf("%d l:", node->key);
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