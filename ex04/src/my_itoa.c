#include <stdlib.h>

char* my_itoa(int nmb){
  int base = 10;
  int max_length = 12;
  int i = 0;
  int j = 0;
  int positive = (nmb < 0 ? -1 : 1);
  char* str = (char*)malloc(max_length);
  char* res = (char*)malloc(max_length);
  if(nmb == 0){
    *str = '0';
    *(str + 1) = '\0';
    return str;
  }
  nmb = nmb*positive;
  while(nmb){
    *(str + (i++)) = '0' + nmb%base;
    nmb /= base;
  }
  if(positive < 0){
    *res = '-';
    j++;
  }
  *(res + (i--)) = '\0';
  while(i >= 0){
    *(res + j) =* (str + i);
     i--, j++ ;
  }
  return res;
 }
