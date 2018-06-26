#include "filler.h"
#include "my_string.h"

void     timeout_reset (struct timeval *timer)
{
	timer->tv_sec = 1;
	timer->tv_usec = 0;
}

void     start_game (filler_t *filler)
{
  struct timeval   timeout;
  req_t            *req;
  int              ret __attribute__((unused));
  fd_set           rfds, wfds;
  pos_t            p;

  req = NULL;
  mylogs("myfiller.log", "w", "My filler: \n");

  create_req(req);
  set_nonblocking(0);
  while(1)
  {
    FD_ZERO(&rfds);
		FD_ZERO(&wfds);
    if(filler->status)
			FD_SET(1, &wfds);
    else
			FD_SET(0, &rfds);
    timeout_reset(&timeout);

    mylogs("myfiller.log", "a", "Status:%s\n", filler->status ? "writing" : "reading");

    ret = select(2, &rfds, &wfds, NULL, &timeout);

    if(FD_ISSET(0, &rfds))
    {
      req = read_request(filler);
      if(req != NULL)
	  {
	    p = play(req);
	    filler->status = 1;
	  }
    }

    if(FD_ISSET(1, &wfds))
	  {
      mylogs("myfiller.log", "a", "Position: %d %d\n", p.x, p.y);
	    print_pos(p);
	    filler->status = 0;
      string_destroy(filler->current_stream);
	    filler->current_stream = NULL;
	  }
  }
};

/*Functions for printing*/
void     print_pos (pos_t p)
{
  dprintf(1, "%d %d", p.x, p.y);
};

