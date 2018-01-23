CC	= gcc -g

RM	= rm -f

NAME	= my_ls

DIR	= ./src/

LDFLAGS = -L ./lib/ -lmy
INCLUDE	= -I ./include/
CFLAGS	= -W -Wall -Werror -Wextra -pedantic $(INCLUDE)

SRC	=	$(DIR)func.c		\
		$(DIR)main.c		\
		$(DIR)majmin.c		\
		$(DIR)print_all.c	\
		$(DIR)print_base.c	\
		$(DIR)rec.c		\
		$(DIR)sort_n.c		\
		$(DIR)sort_t.c		\
		$(DIR)utils.c

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
