#include "filler.h"
#include "my_string.h"

int      set_nonblocking(int fd)
{
  int flags = fcntl(fd, F_GETFL, 0);
	return (fcntl(fd, F_SETFL, flags | O_NONBLOCK));
};

void     fatal(char *msg)
{
  dprintf(2, "%s ", msg);
  exit (1);
};

void     create_filler(filler_t *filler)
{
  filler->current_stream = NULL;
  filler->status = 0;
};

void     destroy_filler(filler_t *filler)
{
  string_destroy(filler->current_stream);
};

req_t    *create_req()
{
  req_t *req;

  req = (req_t*) malloc(sizeof(req_t));
  return (req);
};

void     destroy_req(req_t *req)
{
  elem_destroy(&req->map);
  elem_destroy(&req->elem);
  free(req);
  req = NULL;
};

void     mylogs(const char *fname, const char *mode, const char *fmt, ...)
{
  va_list   args;
  FILE      *logger;

  logger = fopen(fname, mode);
  va_start(args, fmt);
  vfprintf(logger, fmt, args);
  va_end(args);
  fclose(logger);
};

