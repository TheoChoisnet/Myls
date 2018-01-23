CC	= gcc

RM	= rm -f

NAME	= libmy.a

FLAGS	= -W -Wall -Werror -Wextra -pedantic -ansi

SRC	=	my_getnbr.c		\
		my_putchar.c		\
		my_putnbr_base.c	\
		my_put_nbr.c		\
		my_putstr.c		\
		my_revstr.c		\
		my_show_wordtab.c	\
		my_strcat.c		\
		my_strcmp.c		\
		my_strcpy.c		\
	        my_strdup.c		\
		my_strlcat.c		\
		my_strlen.c		\
		my_strncat.c		\
	    	my_strncmp.c		\
	     	my_strncpy.c		\
	     	my_strstr.c		\
	        my_str_to_wordtab.c	\
		my_strcut.c

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc ../$(NAME) $(OBJ)
	cp my.h ../../include/

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
