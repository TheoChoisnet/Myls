#include	"my.h"
#include	"my_ls.h"

int		is_hidden_dir(char *name, t_opt *opt)
{
  if (name[0] == '.')
    {
      if (opt->a == 1 || opt->f == 1)
	return (1);
      else
	return (0);
    }
  return (1);
}

int		tab_size(char **tab, char *path, t_opt *opt, int i)
{
  struct stat	stats;
  char		*tmp;
  int		nb;

  nb = 0;
  while (tab[i])
    {
      tmp = my_strcat(path, tab[i]);
      lstat(tmp, &stats);
      if (S_ISDIR(stats.st_mode) && my_compare(tab[i], "..") != 0 &&
	  my_compare(tab[i], ".") != 0)
	nb += is_hidden_dir(tab[i], opt);
      free(tmp);
      i++;
    }
  return (nb);
}

char		**take_only_dir(char **tab, char *path, t_opt *opt, int i)
{
  struct stat	stats;
  char		*tmp;
  char		**nwtab;
  int		j;
  int		len;

  j = 0;
  len = tab_size(tab, path, opt, 0);
  if ((nwtab = malloc(sizeof(char*) * (len + 1))) == NULL)
    my_exit(ERROR_MALLOC, NULL);
  while (tab[i])
    {
      tmp = my_strcat(path, tab[i]);
      lstat(tmp, &stats);
      if (S_ISDIR(stats.st_mode))
	if (my_compare(tab[i], "..") != 0 &&
	    my_compare(tab[i], ".") != 0 && is_hidden_dir(tab[i], opt) == 1)
	  nwtab[j++] = my_strdup(tmp);
      free(tmp);
      i++;
    }
  nwtab[j] = NULL;
  return (nwtab);
}

void            launch_rec(char **tab, char *path, t_opt *opt)
{
  char		**tab_dir;
  int		i;

  i = 0;
  if (opt->f == 0)
    tab = sort_tab(tab);
  path = my_strcat(path, "/");
  if (opt->t == 1 && opt->f == 0)
    tab = sort_time(tab, path, 0);
  tab_dir = take_only_dir(tab, path, opt, 0);
  if (opt->r == 1 && opt->f == 0)
    tab_dir = reverse_tab(tab_dir);
  while (tab_dir[i])
    {
      get_data(tab_dir[i], opt, 1);
      i++;
    }
  free(tab_dir);
}
