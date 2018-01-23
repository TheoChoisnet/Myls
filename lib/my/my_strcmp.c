#include	<stdio.h>

int	my_strcmp(char *s1, char *s2)
{
  int   i;
  char	tmp;
  char	tmp2;

  i = 0;
  tmp = s1[i];
  tmp2 = s2[i];
  while (s1[i] && s2[i])
    {
      tmp = s1[i];
      tmp2 = s2[i];
      if (s1[i] >= 'A' && s1[i] <= 'Z')
	tmp += 32;
      if (s2[i] >= 'A' && s2[i] <= 'Z')
	tmp2 += 32;
      if (tmp != tmp2)
	return (tmp - tmp2);
      i++;
    }
  if (my_strlen(s1) <= my_strlen(s2))
    return (-1);
  return (1);
}

int     my_compare(char *s1, char *s2)
{
  int   i;

  i = 0;
  while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
    i++;
  return (s1[i] - s2[i]);
}
