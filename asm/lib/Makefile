##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for lib
##

SRC	=	my/flag_handling.c	\
		my/int_to_str.c	\
		my/my_print.c	\
		my/tools.c	\
		my/tools_2.c	\
		my/tools_3.c	\
		my/tools_4.c	\
		my/strcmp.c	\
		my/str_clean.c	\
		my/strcpy.c	\
		my/strcpy.c		\
		my/char.c 		\
		my/free_array.c	\
		my/strwordarray.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

CPPFLAGS	=	-I./../include/

CFLAGS	=	-Wall -Wextra

all: $(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf my/*~ my/*# ./*~ ./*#

fclean: clean
	rm -rf $(OBJ) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
