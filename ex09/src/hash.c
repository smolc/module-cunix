
#include <stdlib.h>
#include "hash.h"
#include "linked_list.h"

hashtable_t   *hash_create(unsigned int size)
{
  hashtable_t *hash;
  int i;

  if (size)
  {
    hash = (hashtable_t*) malloc(sizeof(hashtable_t));
    hash->table = (void**) malloc(size*sizeof(void*));
    i = 0;
    hash->size = size;
    while (i < size)
      hash->table[i] = 0, i++;
    return (hash);
  }
  return (0);
}

void   hash_destroy(hashtable_t *ht, void (*fp)(void *data))
{
  int i;
  int size;

  i = 0;
  size = ht->size;
  if (ht)
  {
    while (i < size)
      fp(ht->table[i]),i++;
  }
  free(ht->table);
}

unsigned int   hash_func(char *key)
{
  unsigned int hash ;
  int i;

  hash, i = 0;
  if (key)
  {
    while (key[i] != '\0')
      hash += key[i], i++;
  }
  return (hash);
}

void   hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data))
{
  int i;

  i = hash_func(key) % ht->size;
  if (ht->table[i])
    list_push(ht->table[i], ptr);
  else
    ht->table[i] = list_create(ptr);
  fp(key);
}

void   *hash_get(hashtable_t *ht, char *key)
{
  int i;
  node_t *node;

  i = hash_func(key) % ht->size;
  node = ht->table[i];
  return (node ? node->data : 0);
}
