#include "../include/hash.h"

hashtable_t *hash_create(unsigned int size) {
  if( size < 1 ) return NULL;
  hashtable_t *ht = malloc(size * sizeof(hashtable_t));
  ht->table = malloc(size * sizeof(node_t*));
  for( int i = 0; i < size; i++ ) ht->table[i] = NULL;
  ht->size = size;
  return ht;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data,void *key)) {
  for( int i = 0; i < ht->size; i++ ) {
    if(ht->table[i]) {
      node_t *ptr = ht->table[i];
      list_destroy(&(ptr), fp);
    }
  }
  free(ht->table);
  free(ht);
}

unsigned int hash_func(char *key) {
  if( !key ) return 0;
  unsigned int answer = 0;
  while( *key != '\0' ) {
    answer += *key;
    key++;
  }
  return answer;
}

void hash_set(hashtable_t *ht, void *key, void *ptr, void (*fp)(void *data, void *key)) {
  int index = hash_func(key)%ht->size;
  fp(ptr, key);
  if ( !(ht->table[index]) ) ht->table[index] = list_create(ptr, key);
  else list_push(ht->table[index], ptr, key);
}

const void *hash_get(hashtable_t *ht, char *key) {
  int index = hash_func(key)%ht->size;
  if( !(ht->table[index]) ) return NULL;
  node_t* p = ht->table[index];
  return key_find(p, key);
}

void hash_print(hashtable_t *ht) {
  for(int i = 0; i < ht->size; i++)
    if(ht->table[i] != NULL)
      list_print((node_t*)ht->table[i]);
}
