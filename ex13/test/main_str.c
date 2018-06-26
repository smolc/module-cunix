#include "my_string.h"
#include "filler.h"

int   test_create()
{
  stream_t  *stream;

  stream = string_create("filler");
  assert(strcmp(stream->str, "filler") == 0);
  assert(stream->size == 6);
  assert(stream->limit == 64);
  string_destroy(stream);
}

int   test_append()
{
  stream_t  *stream;

  stream = string_create("fffff ");
  string_append(stream, "gggggg");
  assert(strcmp(stream->str, "fffff gggggg") == 0);
  assert(stream->size == 12);
  assert(stream->limit == 64);
  string_destroy(stream);
}

int   test_big_append()
{
  stream_t  *stream;
  char *str;
  str = "This test case have to check reallocing memory, when string is overfilled";
  stream = string_create("This test ");
  string_append(stream, "case have to check reallocing memory, when string is overfilled");
  assert(strcmp(stream->str, str) == 0);
  assert(stream->size == 73);
  assert(stream->limit == 128);
  string_destroy(stream);
}

int   test_small()
{
  test_create();
  test_append();
}

int   test_big()
{
  test_big_append();
}

int   main(int argc, char *argv[])
{
   test_small();
   test_big();
   return(0);
}
