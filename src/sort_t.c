#include	"my.h"
#include	"my_ls.h"

char            **reverse_tab(char **tab)
{
  char          *tmp;
  int           i;
  int           len;
  int           half;

  len = tab_len(tab) - 1;
  half = len / 2;
  i = 0;
  while (i <= half && tab[i])
    {
      tmp = my_strdup(tab[i]);
      tab[i] = my_strdup(tab[len]);
      tab[len] = my_strdup(tmp);
      free(tmp);
      i++;
      len--;
    }
  return (tab);
}

int             size_of_dir(char *path)
{
  DIR           *dir;
  struct dirent *file;
  int           size;

  size = 0;
  if ((dir = opendir(path)) == NULL)
    my_exit(ERROR_OPEN, path);
  while ((file = readdir(dir)) != NULL)
    size++;
  closedir(dir);
  return (size);
}

int             check_dir(char *str)
{
  DIR           *dir;

  if ((dir = opendir(str)) == NULL)
    return (-1);
  return (1);
}

int             is_sorted_time(char **tab, int i, char *str)
{
  char          *tmp1;
  char          *tmp2;
  struct stat   stat1;
  struct stat   stat2;

  while (tab[i + 1])
    {
      tmp1 = my_strcat(str, tab[i]);
      tmp2 = my_strcat(str, tab[i + 1]);
      lstat(tmp1, &stat1);
      lstat(tmp2, &stat2);
      if (stat1.st_mtime < stat2.st_mtime)
        {
          free(tmp1);
          free(tmp2);
          return (-1);
        }
      free(tmp1);
      free(tmp2);
      i++;
    }
  return (1);
}

char            **sort_time(char **tab, char *str, int i)
{
  char          *tmp1;
  char          *tmp2;
  struct stat   stat1;
  struct stat   stat2;

  while (is_sorted_time(tab, 0, str) != 1)
    {
      i = 0;
      while (tab[i + 1])
        {
          tmp1 = my_strcat(str, tab[i]);
          tmp2 = my_strcat(str, tab[i + 1]);
          lstat(tmp1, &stat1);
          lstat(tmp2, &stat2);
          if (stat1.st_mtime < stat2.st_mtime)
            my_swap(&tab[i], &tab[i + 1]);
          free(tmp1);
          free(tmp2);
          i++;
        }
    }
  return (tab);
}
