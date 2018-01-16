#include <stdlib.h>

char   *str(const char *str)
{
  char	*rts;
  int	i;

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

static int   len(int n, int sign)
{
  int l;

  l = 0;
  while (n /= 10)
    l++;
  l += sign;
  return (l);
}

char   *my_itoa(int n)
{
  int l, sign;
  char *s;

  sign = 0;
  if (n == -2147483648)
    return (str("-2147483648"));
  if (n < 0)
    sign = 1, n = -n;
  l = len(n, sign) + 2;
  if ((s = (char*)malloc(sizeof(char) * (l))) == NULL)
    return (0);
  s[--l] = '\0';
  while (l--)
  {
    s[l] = n % 10 + '0';
    n /= 10;
  }
  if (sign)
    s[0] = '-';
  return (s);
}
