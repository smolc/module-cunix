#ifndef _FILLER_H_
#define _FILLER_H_

#include "libs.h"

#define BUF_SIZE 64
#define STR_SIZE 32

typedef struct  elem_s
{
  int           h;
  int           w;
  char          **array;
}               elem_t;

typedef struct  pos_s
{
  int           x;
  int           y;
}               pos_t;

typedef struct  req_s
{
  char          symbol;
  elem_t         map;
  elem_t        elem;
}               req_t;

typedef struct  stream_s
{
  char          *str;
  unsigned int  size;
  unsigned int  limit;
}               stream_t;

typedef struct  filler_s
{
  stream_t      *current_stream;
  int           status;
  int           find_enemy;
}               filler_t;


/*Functions for reading*/
req_t*          read_request(filler_t *filler);
void            read_input(filler_t* filler);

/*Functions for parsing*/
int             get_size(char *res, char *buf, int start);
req_t*          parse_all(char *all);
pos_t           parse_size(char *answer);

/*Functions for content parsing*/
elem_t          elem_init(int w, int h);
elem_t          elem_read(char *buf, int pos, int w, int h);
void            elem_destroy(elem_t *el);

/*Functions for game logic*/
void            start_game(filler_t *filler);
pos_t           play(req_t *core);

/*Functions for printing*/
void            print_pos(pos_t p);

/*Tools*/
int             set_nonblocking(int fd);
void            fatal(char *msg);
void            create_filler(filler_t *filler);
void            destroy_filler(filler_t *filler);
req_t           *create_req();
void            destroy_req(req_t *req);

/*Logger*/
void            mylogs(const char *fname, const char *mode, const char *fmt, ...);

#endif // _FILLER_H_