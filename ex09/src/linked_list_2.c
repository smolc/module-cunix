
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

void   *list_pop(node_t **head)
{
  node_t *temp, *last;
  void *data;

  if (temp == *head)
  {
    data = temp->data;
    return (data);
  }
  last = *head;
  while(last->next)
    last = last->next;
  data = temp->data;
  last->next = NULL;
  return (data);
}

void   *list_shift(node_t **head)
{
  void *data;

  data = (*head)->data;
  head = NULL;
  return (data);
}

void   *list_remove (node_t **head, int pos)
{
  void *data;
  node_t *temp, *delete;

  temp = *head;
  delete  = temp->next;
  data = delete->data;
  free(delete);
  return (data);
}

void   list_print(node_t *head)
{
  node_t *cur;

  cur = head;
  while(cur)
  {
    printf("%s", cur->data);
    cur = cur->next;
  }
}

void   list_visitor(node_t *head, void (*fp)(void     *data))
{
  node_t* pos;

  pos = head;
  while (pos)
  {
    fp(pos->data);
    pos = pos->next;
  }
}