#include	"my.h"
#include	"my_ls.h"

void            print_total(char **tab, char *path, t_opt *opt)
{
  struct stat   stats;
  char          *tmp;
  int           i;
  int           size;

  i = 0;
  size = 0;
  while (tab[i])
    {
      tmp = my_strcat(path, tab[i]);
      lstat(tmp, &stats);
      if (opt->a == 1)
        size += stats.st_blocks;
      else
        if (tab[i][0] != '.')
          size += stats.st_blocks;
      free(tmp);
      i++;
    }
  if (i > 1)
    {
      my_putstr("total ");
      my_put_nbr(size / 2);
      my_putchar('\n');
    }
}

void            print_rights(mode_t mode)
{
  my_putchar(mode & S_IRUSR ? 'r' : '-');
  my_putchar(mode & S_IWUSR ? 'w' : '-');
  my_putchar(mode & S_IXUSR ? 'x' : '-');
  my_putchar(mode & S_IRGRP ? 'r' : '-');
  my_putchar(mode & S_IWGRP ? 'w' : '-');
  my_putchar(mode & S_IXGRP ? 'x' : '-');
  my_putchar(mode & S_IROTH ? 'r' : '-');
  my_putchar(mode & S_IWOTH ? 'w' : '-');
  my_putchar(mode & S_IXOTH ? 'x' : '-');
  my_putchar(' ');
}

void            print_mode(mode_t mode)
{
  if ((mode & S_IFLNK) == S_IFLNK)
    my_putchar('l');
  if (((mode & S_IFMT) == S_IFMT) && (mode & S_IFLNK) != S_IFLNK)
    my_putchar('m');
  if (((mode & S_IFSOCK) == S_IFSOCK) && (mode & S_IFLNK) != S_IFLNK)
    my_putchar('s');
  if (((mode & S_IFREG) == S_IFREG) &&
      (mode & S_IFLNK) != S_IFLNK && (mode & S_IFSOCK) != S_IFSOCK)
    my_putchar('-');
  if (((mode & S_IFDIR) == S_IFDIR) && (mode & S_IFLNK) != S_IFLNK &&
      (mode & S_IFBLK) != S_IFBLK && (mode & S_IFSOCK) != S_IFSOCK)
    my_putchar('d');
  if (((mode & S_IFCHR) == S_IFCHR) && (mode & S_IFLNK) != S_IFLNK &&
      (mode & S_IFBLK) != S_IFBLK)
    my_putchar('c');
  if (((mode & S_IFBLK) == S_IFBLK) && (mode & S_IFLNK) != S_IFLNK)
    my_putchar('b');
  if (((mode & S_IFIFO) == S_IFIFO) && (mode & S_IFLNK) != S_IFLNK)
    my_putchar('p');
}

void            print_time(char *time)
{
  char          *str;
  int           i;
  int           j;

  if ((str = malloc(sizeof(char) * 13)) == NULL)
    my_exit(ERROR_MALLOC, NULL);
  i = 0;
  j = 0;
  while (time[i])
    {
      if (i > 3 && i < 16)
        str[j++] = time[i];
      i++;
    }
  str[j] = 0;
  my_putstr(str);
  my_putchar(' ');
  free(str);
}

void	print_all_data(struct stat stats, t_opt *opt)
{
  print_mode(stats.st_mode);
  print_rights(stats.st_mode);
  my_put_nbr(stats.st_nlink);
  my_putchar(' ');
  if (opt->g == 0)
    {
      my_putstr(getpwuid(stats.st_uid)->pw_name);
      my_putchar(' ');
    }
  if (opt->bg == 0)
    {
      my_putstr(getgrgid(stats.st_gid)->gr_name);
      my_putchar(' ');
    }
  if (S_ISBLK(stats.st_mode) || S_ISCHR(stats.st_mode))
    print_majorminor(stats.st_rdev);
  else
    my_put_nbr(stats.st_size);
  my_putchar(' ');
  print_time(ctime(&stats.st_ctime));
}
