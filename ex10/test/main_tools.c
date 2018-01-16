#include "filler.h"
#include "my_string.h"

int main(int argc, char **argv)
{
  filler_t filler;
  req_t    *request;

  create_filler(&filler);
  filler.current_stream = string_create("Test");
  destroy_filler(&filler);

  return 0;
}