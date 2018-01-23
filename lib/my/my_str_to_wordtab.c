#include	<stdio.h>
#include	<stdlib.h>

int	is_alphnum(char c)
{
  if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || \
      (c >= 'A' && c <= 'Z'))
    return (0);
  return (1);
}

char	**my_str_to_wordtab(char *src)
{
  int	i;
  int	j;
  int	k;
  char	**tab;

  i = 0;
  j = 0;
  if ((tab = malloc(my_strlen(src) * sizeof(char*))) == NULL)
    return (NULL);
  while (i < my_strlen(src))
    {
      if ((tab[j] = malloc(my_strlen(src) * sizeof(char*))) == NULL)
        return (NULL);
      k = 0;
      while (is_alphnum(src[i]) == 1 && i < my_strlen(src))
        i++;
      while (is_alphnum(src[i]) == 0 && i < my_strlen(src))
        tab[j][k++] = src[i++];
      tab[j][k] = '\0';
      j++;
    }
  tab[j] = NULL;
  return (tab);
}
