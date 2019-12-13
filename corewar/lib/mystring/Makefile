##
## EPITECH PROJECT, 2019
## mystring
## File description:
## Makefile
##

NAME	=	libmystring.a

SRC	=	src/ato.c						\
		src/arr.c						\
		src/nbr.c						\
		src/char.c						\
		src/free.c						\
		src/print.c						\
		src/arrlen.c					\
		src/memset.c					\
		src/strcmp.c					\
		src/strcat.c					\
		src/strchr.c					\
		src/strcpy.c					\
		src/strlen.c					\
		src/strepur.c					\
		src/convert.c					\
		src/revstr.c					\
		src/strwordarray.c				\
		src/get_next_line.c				\
		src/my_put_nbr.c				\

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I ./include

RM	=	rm -rf

CC	=	gcc -Wall -Wextra

all:	$(NAME)

$(NAME):	$(OBJ)
		ar rc $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
