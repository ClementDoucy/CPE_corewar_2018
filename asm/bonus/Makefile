##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for asm
##

include ../src/sources.mk
include src/sources.mk

NAME	=	asm

OBJ	=	$(SRCS:.c=.o)

SRCS	:=	$(filter-out ./src/main.c, $(SRCS))

SRCS	:=	$(filter-out ./src/launcher.c, $(SRCS))

SRCS	:= $(addprefix ., $(SRCS))

SRCS	+=	$(SRCSBONUS)

CC	=	gcc

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-I../include

LDFLAGS	=	-L../lib

LIB	=	-lmy

all: $(LIB) $(NAME)

$(LIB):
	make -C ../lib/

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LIB)

clean:
	$(RM) *~ *# vgcore* src/*~ src/*# include/*~ include/*#
	make clean -C ../lib/

fclean: clean
	$(RM) $(NAME) $(OBJ)
	make fclean -C ../lib/

re:	fclean all

.PHONY: all clean fclean re

