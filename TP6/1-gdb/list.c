#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  struct node* next;
  char element[256];
};

struct node* create(char str[]) {
  struct node* res = malloc(sizeof(struct node));

  res->next = NULL;
  strncpy(res->element, str, 256);

  return res;
}

void display(struct node* node) {
  for(; node; node=node->next) {
    printf("%s\n", node->element);
  }
}

struct node* insert(struct node* list, char str[]) {
  struct node* cur_node = list;
  struct node* next_node = NULL;
  struct node* new_node = create(str);


  if(cur_node == NULL) {
    new_node->next = NULL;
    return new_node;
  }
  next_node = cur_node->next;
  /* should we insert at the beginning of the list ? */
  if(strcmp(cur_node->element, str) > 0) {
    new_node->next = cur_node;
    /* the list now starts with new_node */
    return new_node;
  }

  while(next_node && strcmp(next_node->element, str) < 0) {
    cur_node = next_node;
    next_node = next_node->next;
  }
  /* we need to insert new_node between cur_node and next_node */

  new_node->next = next_node;
  cur_node->next = new_node;
  return list;
}

struct node* destroy(struct node* list, char str[]) {
  struct node* cur_node = list;
  struct node* next_node = NULL;

  if(cur_node) {
    next_node = cur_node->next;
    if(strcmp(cur_node->element, str) == 0) {
      /* free the first element of the list */
      free(cur_node);
      /* the list now starts with the second element of the list */
      return next_node;
    }
  }

  while(next_node && (strcmp(next_node->element, str) != 0)) {
    /*
     * browse the list of elements starting from the beginning
     * of the list.
     * for each iteration, next_node is cur_node->next
     */
    cur_node = next_node;
    next_node = next_node->next;
  }

  if(next_node) {
    /* we found the element to remove */
    cur_node->next = next_node->next; /* remove next_node from the list */
    free(next_node);		      /* free the element to remove */
  }
  return list;
}

int main(int argc, char** argv) {
  struct node* n1 = create("bonjour");
  struct node* n2 = create("monde");

  printf("---- aaa bonjour monde ----\n");
  n1->next = n2;
  printf("%s %s\n", n1->element, n2->element);
  display(n1);

  n1 = insert(n1, "aaa");
  display(n1);

  printf("---- que la (-force) soit avec toi ----\n");

  struct node* list = NULL;

  list = insert(list, "que");
  list = insert(list, "la");
  list = insert(list, "force");
  list = insert(list, "soit");
  list = insert(list, "avec");
  list = insert(list, "toi");
  list = destroy(list, "force");
  display(list);
  list = destroy(list, "toi");
  display(list);
  return EXIT_SUCCESS;
}
/* -*- c-file-style: "GNU" -*- */
