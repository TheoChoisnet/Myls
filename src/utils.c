#include	"my.h"
#include	"my_ls.h"

void            my_exit(int nb, char *arg)
{
  if (nb == 1)
    my_putstr("./my_ls: malloc error.\n");
  if (nb == 2)
    {
      my_putstr("./my_ls: cannot access ");
      my_putstr(arg);
      my_putstr(": No such file or directory\n");
    }
  if (nb == 3)
    {
      my_putstr("./my_ls: invalid line width: ");
      my_putstr(arg);
      my_putchar('\n');
    }
  exit(-1);
}

void            init_opt(t_opt *opt)
{
  opt->l = 0;
  opt->d = 0;
  opt->r = 0;
  opt->rec = 0;
  opt->t = 0;
  opt->a = 0;
  opt->c = 0;
  opt->f = 0;
  opt->g = 0;
  opt->bg = 0;
  opt->i = 0;
  opt->nb_dir = 0;
  opt->nb_file = 0;
}

int             path_correct(char *str)
{
  int           i;

  i = my_strlen(str) - 1;
  while (i > 0)
    {
      if (i + 1 < my_strlen(str))
	{
	  if (str[i] == '/' && str[i + 1] != '.')
	    return (1);
	  if (str[i] == '/' && str[i + 1] == '.' && i > 0)
	    return (-1);
	}
      i--;
    }
  return (1);
}

int             is_exec(mode_t mode)
{
  if ((mode & S_IFREG) == S_IFREG)
    {
      if ((mode & S_IXUSR) && (mode & S_IXGRP) && (mode & S_IXOTH))
        return (1);
    }
  return (-1);
}

int             tab_len(char **tab)
{
  int           i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}
