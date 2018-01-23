#ifndef	MY_H_
#define	MY_H_

void	my_putchar(char);
int	my_put_nbr(int);
int	my_putstr(char *);
int	my_strlen(char *);
int	my_getnbr(char *);
char	*my_strcut(char*, int, int);
char	*my_strcpy(char *, char *);
char	*my_strncpy(char *, char *);
char	*my_revstr(char *);
char	*my_strstr(char *, char *);
int	my_strcmp(char *, char *);
int	my_compare(char *, char *);
int	my_strncmp(char *, char *, int);
char	*my_strcat(char *, char *);
char	*my_strncat(char *, char *, int);
int	my_strlcat(char *, char *, int);
char	*my_strdup(char *);
int	my_show_wordtab(char **);
char	**my_str_to_wordtab(char *);

#endif
