#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

node_t *list_create(void *data){
  node_t* head = (node_t*) malloc(sizeof(node_t));
  head->data = data;
  head->next = 0;
  return head;
}

node_t *end(node_t *head){
  while(head->next)
    head = head->next;
  return head;
}

void list_destroy(node_t **head, void (*fp)(void *data)){
  while(*head){
    while((*head)->next)
      list_destroy(&((*head)->next), fp);
    fp((*head)->data);
    free(*head);
    *head = 0;
  }
}

void list_clean(node_t **head){
  while(*head){
    while((*head)->next)
      list_clean(&((*head)->next));
    free(*head);
    *head = 0;
  }
}

void list_push(node_t *head, void *data){
  node_t *temp = end(head);
  temp->next = list_create(data);
}

void list_unshift(node_t **head, void *data){
  if(*head){
    node_t *temp = list_create(data);
    temp->next = *head;
    *head = temp;
  }
}

void *list_pop(node_t **head){
  node_t *temp = end(*head);
  if (temp == *head){
    void *data = temp->data;
    return data;
  }
  node_t *last = *head;
  while(last->next)
    last = last->next;
  void *data = temp->data;
  last->next = 0;
  return data;
}

void *list_shift(node_t **head){
  void *data = (*head)->data;
  data = (*head)->data;
  head = 0;
  return data;
}

void *list_remove(node_t **head, int pos){
  node_t *temp = *head;
  node_t *delete = temp->next;
  void *data = delete->data;
  free(delete);
  return data;
}

void list_print(node_t *head){
  node_t* cur = head;
  while(cur){
     printf("%s", cur->data);
     cur = cur->next;
  }
}

void list_visitor(node_t *head, void (*fp)(void *data)){
  node_t* pos = head;
  while(pos){
    fp(pos->data);
    pos = pos->next;
  }
}