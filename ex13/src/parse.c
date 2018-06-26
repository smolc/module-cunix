#include "filler.h"
#include "my_string.h"

/*Functions for parsing*/
req_t*          parse_all(char *all)
{
  req_t     *req;
  pos_t     size;
  int       pos, n;
  char      str[BUF_SIZE], str2[BUF_SIZE];

  n = 0;
  pos = 2;
  req = create_req();
  req->symbol = all[0];
  memset(str, '\0', BUF_SIZE);

  // parse map
  do
  {
    str[n] = all[pos];
    pos++;
    n++;
  } while (all[pos - 1] != '\n');
  size = parse_size(str);
  req->map = elem_read(all, pos, size.y, size.x);
  pos += req->map.h * (req->map.w + 1);

  // parse figure
  n = 0;
  do
  {
    str2[n] = all[pos];
    pos++;
    n++;
  } while (all[pos - 1] != '\n');

  size = parse_size(str2);
  req->elem = elem_read(all, pos, size.y, size.x);

  mylogs("myfiller.log", "a", "(parse.c -> parse_all) My symbol: %c.\n", req->symbol);
  mylogs("myfiller.log", "a", "(parse.c -> parse_all) Map size: %d x %d.\n", req->map.h, req->map.w);
  mylogs("myfiller.log", "a", "(parse.c -> parse_all) Element size: %d x %d.\n", req->elem.h, req->elem.w);

  return (req);
};

pos_t           parse_size(char *answer)
{
  pos_t     pos;
  int       i, size;
  char      *l, *r;

  size = strlen(answer);
  l = malloc(size);
  r = malloc(size);
  memset(l, '\0', size);
  memset(r, '\0', size);
  for(i = 0; i < size && answer[i] != ' '; i++);
  l = strncpy(l, answer, i);
  r = strcpy(r, answer + i + 1);
  pos.x = atoi(l);
  pos.y = atoi(r);
  free(l);
  free(r);
  return pos;
};

