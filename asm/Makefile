##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for asm
##

include src/sources.mk

NAME	=	asm

OBJ	=	$(SRCS:.c=.o)

CC	=	gcc

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-I./include

LDFLAGS	=	-L./lib

LIB	=	-lmy

all:	$(LIB) $(NAME)

$(LIB):
	make -C ./lib/

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LIB)

clean:
	$(RM) *~ *# vgcore* src/*~ src/*# include/*~ include/*#
	make clean -C ./lib/
	make clean -C ./tests/

fclean: clean
	$(RM) $(NAME) $(OBJ)
	make fclean -C ./lib/
	make fclean -C ./tests/

re:	fclean all

tests_run:
	make re -C ./tests/

.PHONY: all clean fclean re tests_run

