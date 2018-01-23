#ifndef		_MY_LS_H_
# define	_MY_LS_H_

# define ERROR_MALLOC (1)
# define ERROR_OPEN (2)
# define ERROR_OPTION (3)

# define BLUE "34"
# define GREEN "32"
# define PINK "35"
# define YELLOW "33"

#include        <dirent.h>
#include        <sys/types.h>
#include        <sys/stat.h>
#include	<fcntl.h>
#include        <unistd.h>
#include        <stdlib.h>
#include        <stdio.h>
#include        <grp.h>
#include        <pwd.h>
#include        <time.h>
#include        <string.h>
#include        <errno.h>

typedef struct	s_opt
{
  int		l;
  int		d;
  int		r;
  int		rec;
  int		t;
  int		a;
  int		c;
  int		f;
  int		g;
  int		bg;
  int		i;
  int		nb_dir;
  int		nb_file;
}		t_opt;

int my_ls(char**, t_opt*, char**, int);
char **sort_dir(char**, t_opt*);
char **sort_time(char**, char*, int);
int is_sorted_time(char**, int, char*);
char **sort_tab(char**);
void my_swap(char**, char**);
int is_sorted(char**);
int check_dir(char*);
int get_opt(int, char**, t_opt*);
int is_good_option(char, t_opt*);
int get_data(char*, t_opt*, int);
int check_av(char*, t_opt*, int);
void init_opt(t_opt*);
int nb_dir(char**);
int nb_file(char**);
void my_exit(int, char*);
int path_correct(char*);
int is_exec(mode_t);
int is_dir(char*);
int tab_len(char**);
char **reverse_tab(char**);
int size_of_dir(char*);
void launch_rec(char**, char*, t_opt*);
char **take_only_dir(char**, char*, t_opt*, int);
int is_hidden_dir(char*, t_opt*);
int tab_size(char**, char*, t_opt*, int);
void print_color(char*, char*, char*);
void print_separate_dir(char*, int, t_opt*);
void print_more(char*, struct stat, t_opt*, char*);
void print_data(char**, int, char*, t_opt*);
void print_ls(char**, char*, t_opt*, int);
void print_total(char**, char*, t_opt*);
void print_rights(mode_t);
void print_mode(mode_t);
void print_time(char*);
void print_all_data(struct stat, t_opt*);
void print_majorminor(dev_t);
int print_only_one(char *, t_opt*, int);
void print_symbolink(char*, struct stat, t_opt*, char*);
void print_name_with_color(char*, struct stat, t_opt*, char*);
void aff_tab(char**);

#endif
