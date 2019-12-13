##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for unit test
##

include tests.mk

NAME	=	unit_tests

SRC	:=	$(filter-out ./../src/main.c, $(SRCTEST))

CC	=	gcc

LDFLAGS	=	-L./../lib -lmy --coverage -lcriterion

RM	=	rm -rf

CPPFLAGS	=	-I./../include

all:	lib $(NAME)

lib:
	make -C ./../lib/

$(NAME):
	$(CC) -o $(NAME) $(SRC) $(CPPFLAGS) $(LDFLAGS)
	./unit_tests
	$(RM) data

clean:
	$(RM) *~ *#

fclean: clean
	$(RM) $(NAME) *.gc*

re:	fclean all

.PHONY: all clean fclean re
