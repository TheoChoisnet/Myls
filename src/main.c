#include	"my.h"
#include	"my_ls.h"

int		check_av(char *arg, t_opt *opt, int nb)
{
  int		i;

  i = 1;
  while (arg[i])
    {
      if ((nb = is_good_option(arg[i], opt)) == -1)
	return (-1);
      if (nb == 0)
	{
	  if (arg[i] == 'a')
	    opt->a = 1;
	  if (arg[i] == 'c')
	    opt->c = 1;
	  if (arg[i] == 'f')
	    opt->f = 1;
	  if (arg[i] == 'g')
	    opt->g = 1;
	  if (arg[i] == 'G')
	    opt->bg = 1;
	  if (arg[i] == 'i')
	    opt->i = 1;
	}
      i++;
    }
  return (0);
}

int		get_opt(int ac, char **av, t_opt *opt)
{
  int		i;
  int		nb;

  i = 1;
  nb = 0;
  if (ac < 2)
    return (0);
  while (i < ac)
    {
      if (av[i][0] == '-')
	{
	  if (check_av(av[i], opt, nb) == -1)
	    my_exit(ERROR_OPTION, av[i]);
	}
      i++;
    }
  return (0);
}

int		get_data(char *path, t_opt *opt, int pos)
{
  DIR		*dir;
  struct dirent	*file;
  char		**tab;
  int		i;

  i = 0;
  if ((dir = opendir(path)) == NULL)
    my_exit(ERROR_OPEN, path);
  if ((tab = malloc(sizeof(char*) * (size_of_dir(path) + 1))) == NULL)
    my_exit(ERROR_MALLOC, NULL);
  while ((file = readdir(dir)) != NULL)
    tab[i++] = my_strdup(file->d_name);
  tab[i] = NULL;
  if (opt->f == 0)
    tab = sort_tab(tab);
  print_ls(tab, path, opt, pos);
  closedir(dir);
  if (opt->rec == 1)
    {
      my_putchar('\n');
      launch_rec(tab, path, opt);
    }
  free(tab);
  return (0);
}

int		my_ls(char **tab, t_opt *opt, char **av, int ac)
{
  int		j;
  int		i;
  int		x;

  i = 1;
  j = 0;
  x = 0;
  while (i < ac)
    {
      if (av[i][0] != '-')
	{
	  if (opt->d == 0 && is_dir(av[i]) == 1)
	    {
	      opt->nb_dir--;
	      get_data(tab[x++], opt, nb_dir(av) > 1 ? 1 : 0);
	    }
	  else
	    print_only_one(av[i], opt, 1);
	  j++;
	}
      i++;
    }
  if (opt->d == 1 && j == 0)
    return (print_only_one(".", opt, 0));
  return (j);
}

int		main(int ac, char **av)
{
  t_opt		*opt;
  char		**tab;

  if ((opt = malloc(sizeof(t_opt))) == NULL)
    my_exit(ERROR_MALLOC, NULL);
  init_opt(opt);
  get_opt(ac, av, opt);
  opt->nb_dir = nb_dir(av);
  opt->nb_file = nb_file(av);
  if (ac > 1 && opt->nb_dir > 0)
    tab = sort_dir(av, opt);
  if (my_ls(tab, opt, av, ac) == 0)
    get_data(".", opt, 0);
  return (0);
}
