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

void display(struct node *initial_node){
    if(initial_node != NULL){
        display(initial_node->next);
    }
}

int main(int argc, char** argv) {
    struct node *n1 = create("bonjour");
    struct node *n2 = create("monde");
    n1->next = n2;
    // (*n1).next = n2; same than n1->next = n2; 
    printf("%p\n", n1);
    printf("n1 element: %s\nn2 element: %s\n", n1->element, n2->element);
    return EXIT_SUCCESS;
}
