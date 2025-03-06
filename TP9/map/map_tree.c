#include <stdio.h>
#include <stdlib.h>
#include "map_tree.h"

struct map* map_init(){
    struct map* my_map = malloc(sizeof(struct map));
    my_map->height = 0;
    my_map->root = NULL;
    return my_map;
}

void map_free(struct map* map){
    if(map->root) {
        free_node(map->root);
    }
}


void free_node(struct node* node) {
    if(node->left) { free_node(node->left); }
    if(node->right) { free_node(node->right); }
    free(node);
}


struct node* insert_node(struct node* tree, struct node* n, int* height) {
    struct node* cur = NULL;
    struct node* next = tree;
    int depth = 0;
    do{
        depth++;
        cur = next;
        if(cur->key < n->key) {
            // if(cur->right) {
            next = cur->right;
            // }
            // else{
            //     cur->right = n;
            // }
        }else if(cur->key > n->key) {
            // if(cur->left) {
                next = tree->left;
            // }
            // else{
            //     cur->left = n;
            // }
        }else{
            cur->val = n->val;
            if(depth > *height) { *height = depth; }
            return tree;
        }
    }while(next != NULL);
    next = n;
    if(depth > *height) { *height = depth; }
    return tree;
}


void map_put(struct map* map, int key, void* val){
    struct node* new_node = malloc(sizeof(struct node));
    new_node->key = key;
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    if(map->root){
        insert_node(map->root, new_node, &map->height);
    }else{
        map->root = new_node;
    }

}

void* map_get(struct map* map, int key){

    struct node* cur = map->root;
    if(cur) {
        // struct node* next;
        do{
            if((*cur).key == key) {
                return (*cur).val;
            }else if((*cur).key < key){
                cur = (*cur).right;
            }else{
                cur = (*cur).left;
            }
        }while(cur != NULL);
    }
    return NULL;
}

void print_tree(struct map* map) {
    if(map->root) {
        struct node* cur = map->root;
        
    }
}

void print_node(struct node* node) {
    
}

// [0]________[1]_[2]_[3]___[1]
//    \_______  \_[3]_    \_[2]
//       \__  \_      \_
//          \_