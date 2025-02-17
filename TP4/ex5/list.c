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
    // printf("\nnew node: %p", my_node);
    // printf("\n&new node: %p\n", &my_node);
    // printf("\nnext node: %p", my_node->next);
    // printf("\n&next node: %p\n", &my_node->next);
    printf("\"%s\" ",my_node->element);
    if(my_node->next != NULL){
        display(my_node->next);
    }else{
        printf("\n");
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


// struct node*rec_insert() {

// }

// void destroy(char* str) {
//     while
// }

int main(int argc, char** argv) {
    // struct node*n1 = create("n1");
    // struct node*n2 = create("n2");
    // n1->next = n2;
    // printf("----------------------------------------------------\n");
    // printf("\nnew node: %p", n1);
    // printf("\n&new node: %p\n", &n1);
    // printf("\nnext node: %p", n1->next);
    // printf("\n&next node: %p\n\n", &n1->next);

    // printf("\nnew node: %p", n2);
    // printf("\n&new node: %p\n", &n2);
    // printf("\nnext node: %p", n2->next);
    // printf("\n&next node: %p\n\n", &n2->next);
    // printf("----------------------------------------------------\n");

    // display(n1);
    // (*n1).next = n2; same than n1->next = n2;
    struct node*linked_list = NULL;
    linked_list = insert(linked_list, "que");
    linked_list = insert(linked_list, "la");
    linked_list = insert(linked_list, "force");
    linked_list = insert(linked_list, "soit");
    linked_list = insert(linked_list, "avec");
    linked_list = insert(linked_list, "toi");
    display(linked_list);
    return EXIT_SUCCESS;
}
