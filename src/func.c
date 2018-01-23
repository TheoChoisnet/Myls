#include	"my.h"
#include	"my_ls.h"

int             nb_file(char **av)
{
  int           i;
  int           nb;
  int           fd;
  int           dir;

  i = 1;
  nb = 0;
  while (av[i])
    {
      if ((fd = open(av[i], O_RDONLY)) != -1 &&
          ((dir = open(av[i], O_DIRECTORY)) == -1))
        nb++;
      i++;
    }
  return (nb);
}

int             nb_dir(char **tab)
{
  DIR           *dir;
  int           i;
  int           nb;

  i = 1;
  nb = 0;
  while (tab[i])
    {
      if ((dir = opendir(tab[i])) != NULL)
        nb++;
      i++;
    }
  return (nb);
}

int             is_dir(char *file)
{
  DIR           *dir;

  if ((dir = opendir(file)) == NULL)
    return (-1);
  closedir(dir);
  return (1);
}
