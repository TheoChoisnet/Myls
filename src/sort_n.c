#include	"my.h"
#include	"my_ls.h"

int             is_sorted(char **tab)
{
  int           i;

  i = 0;
  while (tab[i + 1])
    {
      if (my_strcmp(tab[i], tab[i + 1]) > 0)
        return (-1);
      i++;
    }
  return (1);
}

void            my_swap(char **s1, char **s2)
{
  char          *tmp;

  if ((tmp = malloc(sizeof(char) * my_strlen(*s2))) == NULL)
    my_exit(ERROR_MALLOC, NULL);
  tmp = *s2;
  *s2 = *s1;
  *s1 = tmp;
}

char            **sort_tab(char **tab)
{
  int           i;

  while (is_sorted(tab) != 1)
    {
      i = 0;
      while (tab[i + 1])
        {
          if (my_strcmp(tab[i], tab[i + 1]) > 0)
            my_swap(&tab[i], &tab[i + 1]);
          i++;
        }
    }
  return (tab);
}

char            **sort_dir(char **av, t_opt *opt)
{
  char          **tab;
  int           nbdir;
  int           i;
  int           j;

  i = 1;
  j = 0;
  nbdir = nb_dir(av);
  if ((tab = malloc(sizeof(char*) * (nbdir + 1))) == NULL)
    my_exit(ERROR_MALLOC, NULL);
  while (av[i])
    {
      if (av[i][0] != '-' && check_dir(av[i]) == 1)
        tab[j++] = my_strdup(av[i]);
      i++;
    }
  tab[j] = NULL;
  tab = sort_tab(tab);
  if (opt->t == 1)
    tab = sort_time(tab, "", 0);
  return (tab);
}
