#include	<stdio.h>

#include	"my.h"
#include	"my_ls.h"

void            print_color(char *file, char *color, char *beg)
{
  char          *tmp;

  tmp = my_strcat(beg, "\033[");
  tmp = my_strcat(tmp, color);
  tmp = my_strcat(tmp, "m");
  tmp = my_strcat(tmp, file);
  tmp = my_strcat(tmp, "\033[0m");
  my_putstr(tmp);
  free(tmp);
}

void		print_name_with_color(char *file, struct stat stats,
				      t_opt *opt, char *path)
{
  if ((stats.st_mode & S_IFSOCK) == S_IFSOCK)
    print_color(file, PINK, "");
  else
    {
      if ((stats.st_mode & S_IFLNK) == S_IFLNK)
	print_symbolink(file, stats, opt, path);
      else
	{
	  if ((stats.st_mode & S_IFDIR) == S_IFDIR)
	    print_color(file, BLUE, "");
	  if ((stats.st_mode & S_IFCHR) == S_IFCHR)
	    print_color(file, YELLOW, "");
	  if ((stats.st_mode & S_IFREG) == S_IFREG)
	    {
	      if (is_exec(stats.st_mode) == 1)
		print_color(file, GREEN, "");
	      else
		my_putstr(file);
	    }
	}
    }
}

void            print_more(char *file, struct stat stats,
			   t_opt *opt, char *path)
{
  if (opt->i == 1)
    {
      my_put_nbr(stats.st_ino);
      my_putchar(' ');
    }
  if (opt->l == 1)
    print_all_data(stats, opt);
  if (opt->c == 1 && opt->f == 0)
    {
      if (((stats.st_mode & S_IFBLK) == S_IFBLK) ||
	  ((stats.st_mode & S_IFMT) == S_IFMT) ||
	  ((stats.st_mode & S_IFIFO) == S_IFIFO))
        my_putstr(file);
      else
        print_name_with_color(file, stats, opt, path);
    }
  else
    {
      if (((stats.st_mode & S_IFLNK) == S_IFLNK))
	print_symbolink(file, stats, opt, path);
      else
	my_putstr(file);
    }
  my_putchar('\n');
}

void            print_data(char **tab, int i, char *path, t_opt *opt)
{
  struct stat   stats;
  char          *tmp;

  while (tab[i])
    {
      if (opt->a == 1 || opt->f == 1)
        {
	  if ((opt->f == 1 && my_compare(tab[i], ".") != 0 &&
	       my_compare(tab[i], "..") != 0) || opt->a == 1)
	    {
	      tmp = my_strcat(path, tab[i]);
	      lstat(tmp, &stats);
	      print_more(tab[i], stats, opt, path);
	      free(tmp);
	    }
        }
      else
        if (tab[i][0] != '.')
          {
            tmp = my_strcat(path, tab[i]);
            lstat(tmp, &stats);
            print_more(tab[i], stats, opt, path);
            free(tmp);
          }
      i++;
    }
}

void            print_ls(char **tab, char *path, t_opt *opt, int pos)
{
  if (path_correct(path) == 1 && tab[0] != NULL)
    {
      print_separate_dir(path, pos, opt);
      path = my_strcat(path, "/");
      if (opt->l == 1 && opt->d == 0)
        print_total(tab, path, opt);
      if (opt->t == 1 && opt->f == 0)
        tab = sort_time(tab, path, 0);
      if (opt->r == 1 && opt->f == 0)
        tab = reverse_tab(tab);
      print_data(tab, 0, path, opt);
      if ((opt->nb_dir > 0 || opt->nb_file > 0) && opt->rec != 1)
	my_putchar('\n');
    }
}
