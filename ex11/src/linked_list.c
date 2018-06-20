#include "../include/linked_list.h"

node_t *list_create(void *data, void *key) {
  node_t *curr = malloc(sizeof(node_t));
  if(curr == NULL) return NULL;
  curr->key = key;
  curr->data = data;
  curr->next = NULL;
  return curr;
}

void list_destroy(node_t **head, void (*fp)(void *data, void *key)){
  if(*head == NULL) return;
  node_t *curr = *head;
  head = NULL;
  node_t *del;
  while (curr != NULL) {
    fp(curr->data, curr->key);
    free(curr->data);
    free(curr->key);
    del = curr;
    curr = curr->next;
    free(del);
  }
  free(head);
}

void list_push(node_t *head, void *data, void *key) {
  if(head == NULL) return;
  node_t *curr = head;
  while(curr->next != NULL) {
    if(!(strcmp(key,(char*)curr->key))) {
      free(key);
      curr->data = data;
      return;
    }
    curr=curr->next;
  }
  if(!(strcmp(key,(char*)curr->key))) {
    free(key);
    curr->data = data;
  }
  else {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = data;
    new_node->key = key;
    new_node->next = NULL;
    curr->next = new_node;
  }
}

void list_unshift(node_t **head, void *data, void *key) {
  node_t *first = malloc(sizeof(node_t));
  first->data = data;
  first->key = key;
  first->next = *head;
  *head = first;
}

void *list_pop(node_t **head) {
  if(*head == NULL) return NULL;
  if((*head)->next == NULL) {
    free(*head);
    *head = NULL;
    return NULL;
  }
  node_t *curr = *head;
  while(curr->next->next != NULL){
    curr = curr->next;
  }
  free(curr->next->data);
  free(curr->next);
  curr->next = NULL;
}

void list_print(node_t *head) {
  node_t *curr = head;
  while(curr != NULL) {
    printf("%s: %s\n", curr->key, curr->data);
    curr = curr->next;
  }
}

void *list_shift(node_t **head) {
  if(*head == NULL) return NULL;
  node_t* curr = *head;
  *head = curr->next;
  free(curr->key);
  free(curr->data);
  free(curr);
}

void *list_remove(node_t **head, int pos) {
  if(*(head) == NULL) return NULL;
  if(pos == 0) return list_shift(head);
  node_t *p = *head;
  node_t *cur = (*head)->next;
  for(int num = 1; num != pos; num++) {
    p = p->next;
    cur = cur->next;
  }
  p->next = cur->next;
  free(cur->key);
  free(cur->data);
  free(cur);
}

void list_visitor(node_t *head, void (*fp)(void *data, void *key)) {
  while(head) {
    fp(head->data, head->key);
    free(head->data);
    free(head->key);
    head = head->next;
  }
}

const void *key_find(node_t *head,char *key) {
   while(head) {
     if(strcmp(key,(char*)head->key) == 0)
       return head->data;
     head = head->next;
   }
   return NULL;
}

