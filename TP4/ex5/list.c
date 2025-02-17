#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    struct node* next;
    char element[256];
};

struct node* create(const char *input){
    struct node *new_node = malloc(sizeof(struct node));
    new_node->next = NULL;
    
    int n = 0;
    const char*cur_char = input;
    while(*cur_char != '\0') {
        n++;
        if(n > 256) {
            printf("input string length superior to 256");
            return NULL;
        }
        cur_char++;
    }
    strncpy(new_node->element, input, n+1);
    return new_node;
}

void display(struct node *my_node){
    if(my_node != NULL) {
        printf("\"%s\" ",my_node->element);
        if(my_node->next != NULL){
            display(my_node->next);
        }else{
            printf("\n");
        }
    }else {
        printf("The list is empty\n");
    }
}

struct node* insert(struct node* list, char* str) {
    struct node *new_node = create(str);
    if (list == NULL){
        new_node->next = NULL;
        list = new_node;
        return new_node;
    } else if(strcmp(list->element, new_node->element) > 0){
        new_node->next = list;
        return new_node;
    } else {
        struct node*next_node = list->next;
        struct node*cur_node = list;
        while(cur_node->next != NULL) {
            if(strcmp(str, next_node->element) < 0) {
                break;
            }else {
                cur_node = next_node;
                next_node = cur_node->next;
            }
        }
        new_node->next = NULL;
        cur_node->next = new_node;
        return list;
    }
}


struct node*rec_insert(struct node*list, char* str) {
    struct node *new_node = create(str);
    if (list == NULL){
        new_node->next = NULL;
        list = new_node;
        return new_node;
    } else if(strcmp(list->element, new_node->element) > 0){
        new_node->next = list;
        return new_node;
    } else {
        list->next = rec_insert(list->next, str);
        
        return list;
    }
}

struct node* destroy(struct node*list, char* str) {
    struct node* cur_node = list;
    if (list == NULL) {
        return NULL;
    }
    while(cur_node->next != NULL){
        if(strcmp(cur_node->next->element, str) == 0) {
            break;
        }
        cur_node = cur_node->next;
    }
    struct node*node_to_delete = cur_node->next;
    cur_node->next = cur_node->next->next;
    free(node_to_delete);
    return list;
}

int main(int argc, char** argv) {
    struct node*linked_list = NULL;
    linked_list = rec_insert(linked_list, "aaa");
    linked_list = rec_insert(linked_list, "bbb");
    linked_list = rec_insert(linked_list, "ddd");
    linked_list = rec_insert(linked_list, "ccc");
    linked_list = destroy(linked_list, "ccc");
    
    // linked_list = insert(linked_list, "que");
    // linked_list = insert(linked_list, "la");
    // linked_list = insert(linked_list, "force");
    // linked_list = insert(linked_list, "soit");
    // linked_list = insert(linked_list, "avec");
    // linked_list = insert(linked_list, "toi");
    display(linked_list);
    return EXIT_SUCCESS;
}
