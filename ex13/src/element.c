#include "filler.h"
#include "my_string.h"

elem_t     elem_init (int w, int h)
{
  elem_t     el;

  el.array = malloc(h * sizeof(char *));
  for(int i = 0; i < h; i++)
    el.array[i] = malloc((w + 1) * sizeof(char));
  el.h = h;
  el.w = w;
  mylogs("myfiller.log", "a", "(element.c -> elem_init) Element inited: %d x %d (w,h).\n", el.h, el.w);
  return (el);
};

elem_t     elem_read (char *buf, int pos, int w, int h)
{
  elem_t     el;

  el = elem_init(w, h);
  mylogs("myfiller.log", "a", "(element.c -> elem_read) Matrix:\n");
  for (int i = 0; i < el.h; i++)
  {
    for (int j = 0; j <= el.w; j++)
    {
      el.array[i][j] = buf[pos];
      mylogs("myfiller.log", "a", "%c", el.array[i][j]);
      pos++;
    }
  }
  mylogs("myfiller.log", "a", "\n");
  return (el);
};

void       elem_destroy (elem_t *el)
{
  for (int i = 0; i < el->h; i++ )
    free(el->array[i]);
  free(el->array);
  el->array = NULL;
  mylogs("myfiller.log", "a", "(element.c -> elem_destroy) Element destroyed.\n");
};

