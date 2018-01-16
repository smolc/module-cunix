#include <stdlib.h>
#include "my_strlen_atoi_itoa.h"

unsigned int   my_strlen(char *str)
{
  unsigned int i;

  i = 0;
  while (*str++ != '\0')
    i++;
  return (i);
}


char   *strdup(const char *str)
{
  char	*rts;
  int		i;

  i = -1;
  while (str[++i]);
  if (!(rts = (char*)malloc(i + 1)))
  	return (0);
  i = 0;
  while (str[i] != '\0')
  {
  	rts[i] = str[i];
  	i++;
  }
  rts[i] = '\0';
  return (rts);
}

static int   dop_len(int n, int sign)
{
 	int len;

  len = 0;
  while (n /= 10)
 		len++;
  len += sign;
  return (len);
}

char   *my_itoa(int n)
{
 	int	len, sign;
 	char *s;

 	sign = 0;
  if (n == -2147483648)
 		return (strdup("-2147483648"));
 	if (n < 0)
    sign = 1, n = -n;
  len = dop_len(n, sign) + 2;
  if ((s = (char*)malloc(sizeof(char) * (len))) == NULL)
    return (0);
  s[--len] = '\0';
  while (len--)
  {
    s[len] = n % 10 + '0';
 		n /= 10;
  }
  if (sign)
     s[0] = '-';
  return (s);
}

int   my_atoi(const char *nptr)
{
  int num, k, i;

  num = 0;
  k = (*nptr == '-' ? -1 : 1);
  i = (k == -1 ? 1 : 0);
  while (*(nptr + i) >= '0' && *(nptr + i) <= '9')
  {
    num = num*10 + (*(nptr + i) - '0');
    i++;
  }
  return (num*k);
}