#include "filler.h"
#include "my_string.h"

int     get_size (char *res, char *buf, int start)
{
  int     end;

  end = 0;
  do
  {
    res[end] = buf[start];
    start++;
    end++;
  } while (buf[start-1] != '\n');
  res[end] = '\0';
  start++;

  mylogs("myfiller.log", "a", "(read.c -> get_size) Size of element is: %d.\n", (end - 1));

  return (end - 1);
}

int     readed (stream_t* buf)
{
  int     pos, elem_pos;
  bool    first_size;
  char    arr_el_size[STR_SIZE];
  pos_t   el_size;

  pos = 0;
  elem_pos = 0;
  first_size = true;

  while(pos <= (int)buf->size)
  {
    if(buf->str[pos] > '9' || buf->str[pos] < '0')
      pos++;
    else if (first_size)
    {
      while(pos <= (int)buf->size && buf->str[pos] != '\n')
        pos++;
      pos++;
      first_size = false;
    }
    else
    {
      elem_pos = pos;
      while(pos <= (int)buf->size && buf->str[pos] != '\n')
        pos++;
      if(buf->str[pos] != '\n')
        return (-1);
      else
      {
        get_size(arr_el_size, buf->str, elem_pos);
        el_size = parse_size(arr_el_size);
        if((int)buf->size <= pos + el_size.x*(el_size.y + 1))
          return (-1);
        else
          return (0);
      }
    }
  }
  return (-1);
};

req_t*     read_request (filler_t *filler)
{
  req_t   *req = NULL;
	read_input(filler);
	if(readed(filler->current_stream) == 0)
		req = parse_all(filler->current_stream->str);
	return req;
};

void     read_input (filler_t* filler)
{
  char   buffer[BUF_SIZE];
  int    res __attribute__((unused));

  while(1)
  {
    memset(buffer, '\0', BUF_SIZE);
    res = read(0, buffer, BUF_SIZE - 1);
    if(!strlen(buffer))
    {
      mylogs("myfiller.log", "a", "(read.c -> read_input) Buffer is empty.\n");
      break;
    }
	if(filler->current_stream == NULL)
    {
      mylogs("myfiller.log", "a", "(read.c -> read_input) Creating string.\n");
      filler->current_stream = string_create(buffer);
    }
    else
    {
      mylogs("myfiller.log", "a", "(read.c -> read_input) String append.\n");
	    string_append(filler->current_stream, buffer);
    }
  }
};

