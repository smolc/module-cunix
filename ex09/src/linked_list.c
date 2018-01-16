
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

node_t   *list_create(void *data)
{
  node_t *head;

  head = (node_t*) malloc(sizeof(node_t));
  head->data = data;
  head->next = NULL;
  return (head);
}

void   list_destroy(node_t **head, void (*fp)(void *data))
{
  while (*head)
  {
    while ((*head)->next)
      list_destroy(&((*head)->next), fp);
    fp((*head)->data);
    free(*head);
  }
}

void   list_clean(node_t **head)
{
  while (*head)
  {
    while ((*head)->next)
      list_clean(&((*head)->next));
    free(*head);
  }
}

void   list_push(node_t *head, void *data)
{
  node_t *temp;

  temp->next = list_create(data);
}

void   list_unshift(node_t **head, void *data)
{
  node_t *temp;

  if (*head)
  {
    temp = list_create(data);
    temp->next = *head;
    *head = temp;
  }
}
