#include "llist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//llist methods

void llist_insert_head(struct node **head, struct node *n){
  //printf("llist_insert_head\n");
  n->next = *head;
  *head = n;
}

struct node *llist_delete_head(struct node **head){
  //printf("llist_delete_head\n");
  struct node *old_node = *head;
  if(old_node != NULL){
    *head = old_node->next;
    return old_node;
  }else{
    return NULL;
  }

}

void llist_insert_tail(struct node **head, struct node *n){
  //printf("llist_insert_tail\n");
  struct node *node = *head;

  if(*head == NULL){
    *head = n;
  }else{
    while(node->next != NULL){
      node = node->next;
    }
    node->next = n;
  }


}

void llist_print(struct node *head){
  //printf("llist_print\n");
  if(head == NULL){
    printf("[empty]\n");
    return;
  };

  struct node * node = head;
  printf("%d", node->value);

  while(node->next != NULL){
    node = node->next;
    printf(" -> %d", node->value);
  }
  printf("\n");
  return;
}

void llist_free(struct node **head){
  //printf("llist_free\n");
  struct node *node = *head;
  struct node *prev_node;

  while(node != NULL){
    prev_node = node;
    node = node->next;
    node_free(prev_node);
  }
  *head = NULL;
}


//Node methods

struct node *node_alloc(int value){
  //printf("node_alloc\n");
  struct node *new_node = malloc(sizeof(struct node));
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

void node_free(struct node *n){
  //printf("node_free\n");
  free(n);
}
