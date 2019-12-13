##
## EPITECH PROJECT, 2019
## Corewar
## File description:
## Lib Makefile
##

LIBS	+=	-L ./lib/mylist -lmylist
LIBS	+=	-L ./lib/mystring -lmystring

MKLIB	=	$(MAKE) -C ./lib/