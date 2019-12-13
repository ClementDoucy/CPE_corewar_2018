##
## EPITECH PROJECT, 2019
## mystring
## File description:
## Makefile
##

NAME	=	libmylist.a

SRC	=	src/linked_list.c			\
		src/destroy_list.c			\
		src/new_nodes.c				\
		src/remove_nodes.c			\
		src/split_list.c			\
		src/list_to_arr.c			\

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
