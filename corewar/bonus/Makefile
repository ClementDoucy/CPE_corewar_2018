##
## EPITECH PROJECT, 2019
## corewar
## File description:
## Makefile
##

include lib/libs.mk
include src/sources.mk
include tests/tests.mk

NAME		=	corewar

CC			=	gcc

CPPFLAGS	=	-I ./include

CFLAGS		=	-Wall -Wextra

OBJ			=	$(SRCS:.c=.o)

RM			=	rm -rf

all:	$(NAME)

$(NAME):	$(OBJ)
		$(MKLIB)
		$(CC) -o $(NAME) $(OBJ) $(LIBS)

clean:
		$(RM) $(OBJ)
		$(MKLIB) clean
		$(MKTESTS) clean

fclean:	clean
		$(RM) $(NAME)
		$(MKLIB) fclean
		$(MKTESTS) fclean

tests_run: all
		$(MKTESTS)

re:	fclean all

.PHONY:	all clean fclean re tests_run
