#ifndef _FILLER_H_
#define _FILLER_H_

#define BUF_SIZE 64

typedef struct collect_s
{
  int           h;
  int           w;
  char          **array;
}               collect_t;

typedef struct  pos_s
{
  int           x;
  int           y;
}               pos_t;

typedef struct  req_s
{
  char          symbol;
  collect_t     map;
  collect_t     elem;
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
req_t*          parse_all(char *all);
pos_t           parse_size(char *answer);
int             find_size(char *dist, char *source, int start);

/*Functions for game logic*/
void            start_game(filler_t *filler);
pos_t           play(req_t *core);

/*Functions for printing*/
void            print_pos(pos_t p);

/*Tools*/
collect_t       collect_init(int width, int height);
collect_t       collect_read(char *source, int pos, int w, int h);
void            collect_destroy(collect_t *col);
int             set_nonblocking(int fd);
void            fatal(char *msg);
void            create_filler(filler_t *filler);
void            destroy_filler(filler_t *filler);
req_t           *create_req();
void            destroy_req(req_t *req);
void            printlog(const char *filename, const char *mode, const char *format, ...);
#endif // _FILLER_H_
