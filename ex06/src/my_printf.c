#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_strlen_atoi_itoa.h"

void   sprint(const char *str)
{
  int i;

  i = 0;
  for (i; *(str + i) != '\0'; i++)
     write(1, str + i, 1);
}

int   ncount(const char *str)
{
  int n;

  n = 0;
  while(*(str + n) >= '0' && *(str++) <= '9')
    n++;
  return (n);
}

int   chprint(int q, const char out)
{
  int i;

  i = 0;
  for (i; i < q; i++)
    write(1, &out, 1);
}

int   type_printf(const char *format, va_list *args)
{
  int q, l, skip;
  char *word;

  q, l, skip, word = NULL;
  switch (*format)
  {
    case '%' : chprint(1,'%'); return (1);
    case 'd' : sprint(my_itoa(va_arg(*args,int))); return (1);
    case 's' : sprint(va_arg(*args,char*)); return (1);
    case '0':
      q = my_atoi(format + 1), skip = ncount(format + 1);
      if (format[skip+1] == 's')
        word = va_arg(*args,char*);
      else
        word = my_itoa(va_arg(*args,int));
      l = my_strlen(word), chprint(q - l, '0'), sprint(word);
      return (skip + 2);
    default :
      q = my_atoi(format), skip = ncount(format);
      if (format[skip] == 's')
        word = va_arg(*args,char*);
      else
        word = my_itoa(va_arg(*args,int));
      l = my_strlen(word), chprint(q - l, ' '), sprint(word);
      return (skip + 1);
  }
}


int   my_printf(const char *format, ...)
{
  int n;
  va_list ar;

  n = 0;
  va_start(ar, format);
  while (format[n] != '\0')
  {
    if (format[n] != '%')
      write(1, format+n, 1),n++;
    else
      n += type_printf(format+n+1,&ar)+1;
  }
  return (0);
}