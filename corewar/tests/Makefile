##
## EPITECH PROJECT, 2019
## corewar
## File description:
## Makefile
##

include ./tests.mk
include ../src/sources.mk

TESTDIR		=	tests

NAME		=	unit_tests

SRCS_TESTS	:=	$(filter-out ./src/main.c, $(SRCS))

SRCS_TESTS	:=  $(addprefix ., $(SRCS_TESTS))

SRCS_TESTS	+=	$(SRC_TEST)

LIB			=	-lcriterion							\
				-L ../lib/mylist -lmylist			\
				-L ../lib/mystring -lmystring		\

GCOVR		=	$(SRCS_TESTS:.c=.gcda)   			\
				$(SRCS_TESTS:.c=.gcno)   			\

CC			=	gcc

RM			=	rm -rf

all:	$(NAME)
		$(CC) -o $(NAME) $(SRCS_TESTS) $(LIB) --coverage -I ../include
		./unit_tests

$(NAME):	$(OBJ_TESTS)

clean:
		$(RM) $(GCOVR)
		$(RM) *.gcno *.gcda

fclean:	clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re tests_run
