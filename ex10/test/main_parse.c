#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "filler.h"

int   test_parse_size()
{
  pos_t     position1, position2, position3;

  position1.x = 10;
  position1.y = 12;
  position2.x = 1053480;
  position2.y = 3423942;
  position3.x = 12345678;
  position3.y = 87654321;
  pos_t res1 = parse_size("10 12");
  pos_t res2 = parse_size("1053480 3423942");
  pos_t res3 = parse_size("12345678 87654321");
  assert(res1.x == position1.x && res1.y == position1.y);
  assert(res2.x == position2.x && res2.y == position2.y);
  assert(res3.x == position3.x && res3.y == position3.y);
}

int   test_find_size()
{
  char      *res1, *res2, *res3;
  char      *expect1, *expect2, *expect3;
  int       pos1, pos2, pos3;

  res1 = malloc(6 * sizeof(char));
  res2 = malloc(6 * sizeof(char));
  res3 = malloc(14 * sizeof(char));
  pos1 = find_size(res1, "1 1\n0\n", 0);
  pos2 = find_size(res2, "Size: 3 3\n ..*\n***\n*..\n", 6);
  pos3 = find_size(res3, "Test size\n10000 13313\n text", 10);
  assert(strcmp(res1, "1 1") == 0);
  assert(strcmp(res2, "3 3") == 0);
  assert(strcmp(res3, "10000 13313") ==  0);
  assert(pos1 == 2);
  assert(pos2 == 8);
  assert(pos3 == 20);
  free(res1);
  free(res2);
  free(res3);
}

int   test_parse_all()
{
  req_t     *request;
  char      *str;
  str = "@\n4 4\n....\n....\n....\n....\n2 2\n*.\n*.\n";
  request = parse_all(str);
  assert(request->map.h == 4 && request->map.w == 4);
  assert(request->elem.h == 2 && request->elem.w == 2);
  destroy_req(request);
}

int   main(int argc, char *argv[])
{
  test_parse_size();
  test_find_size();
  test_parse_all();
  return (0);
}