#include	"my.h"
#include	"my_ls.h"

void            print_separate_dir(char *path, int pos, t_opt *opt)
{
  int		i;

  i = 0;
  if (pos > 0 || opt->rec == 1)
    {
      while (path[i])
	{
	  if (path[i + 1] && path[i] == '/')
	    {
	      if (path[i + 1] != '/')
		my_putchar(path[i]);
	    }
	  else
	    my_putchar(path[i]);
	  i++;
	}
      my_putstr(":\n");
    }
}

int		print_only_one(char *file, t_opt *opt, int nb_path)
{
  struct stat	stats;
  int		fd;

  if ((fd = open(file, O_RDONLY)) == -1)
    my_exit(ERROR_OPEN, file);
  if (nb_path != 0)
    {
      if ((fd = open(file, O_DIRECTORY)) != -1)
	opt->nb_dir--;
      else
	opt->nb_file--;
    }
  lstat(file, &stats);
  print_more(file, stats, opt, "./");
  if (opt->d == 0 && (opt->nb_file > 0 || opt->nb_dir > 0))
    my_putchar('\n');
  return (1);
}

void            print_majorminor(dev_t dev)
{
  my_put_nbr(dev / 256);
  my_putstr(", ");
  my_put_nbr(dev % 256);
}

void		print_symbolink(char *file, struct stat stats,
				t_opt *opt, char *path)
{
  char		*linkname;
  int		read;

  if ((linkname = malloc(sizeof(char) * (stats.st_size + 1))) == NULL)
    my_exit(ERROR_MALLOC, NULL);
  read = readlink(my_strcat(path, file), linkname, stats.st_size + 1);
  if (read < 0)
    my_exit(ERROR_OPEN, file);
  linkname[stats.st_size] = 0;
  if (opt->c == 1)
    {
      print_color(file, GREEN, "");
      my_putstr(" -> ");
      print_color(linkname, YELLOW, "");
    }
  else
    {
      my_putstr(file);
      my_putstr(" -> ");
      my_putstr(linkname);
    }
}

int		is_good_option(char c, t_opt *opt)
{
  if (c != 'l' && c != 'd' && c != 'r' && c != 'R' &&
      c != 't' && c != 'a' && c != 'c' && c != 'f' &&
      c != 'g' && c != 'G' && c != 'i')
    return (-1);
  if (c == 'l' || c == 'd' || c == 'r' || c == 'R' || c == 't')
    {
      if (c == 'l')
	opt->l = 1;
      if (c == 'd')
	opt->d = 1;
      if (c == 'r')
	opt->r = 1;
      if (c == 'R')
	opt->rec = 1;
      if (c == 't')
	opt->t = 1;
      return (1);
    }
  return (0);
}
