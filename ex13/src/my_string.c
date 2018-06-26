#include "my_string.h"

stream_t   *string_init ()
{
  stream_t 	*str;

  str = malloc(sizeof(stream_t));
  str->str = NULL;
  str->size = 0;
  str->limit = 0;
  return (str);
};

stream_t   *string_create (char* str)
{
  stream_t	*ptr;
  int           size;
  int           len;

  size = strlen(str);
  len  = size / BUF_SIZE + 1;

  ptr = string_init();
  ptr->limit = BUF_SIZE * len;
  ptr->size = size;
  ptr->str = malloc(ptr->limit * sizeof(char));
  strcpy(ptr->str, str);
  return (ptr);
};


void     string_append (stream_t *ptr, char* str)
{
  int     size;

  if(!ptr)
    ptr = string_create(str);
  else
  {
    size = strlen(str);
    if(ptr->size + size >= ptr->limit)
    {
      ptr->str = realloc( ptr->str, ptr->limit + size + BUF_SIZE);
      ptr->limit += BUF_SIZE;
      ptr->str[ptr->size + size] = '\0';
    }
    for(int i = 0; i < size; i++)
      ptr->str[ptr->size + i] = str[i];
    ptr->size += size;
    ptr->str[ptr->size] = '\0';
  }
};

void     string_destroy (stream_t *ptr)
{
  free(ptr->str);
  ptr->str = NULL;
  free(ptr);
  ptr = NULL;
};

