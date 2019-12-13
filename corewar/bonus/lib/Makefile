##
## EPITECH PROJECT, 2019
## Corewar
## File description:
## Lib Makefile
##

LIBS	=	./mylist/		\
			./mystring/		\

all:	mklibs

mklibs:
		$(foreach var, $(LIBS), $(MAKE) -C $(var);)

clean:
		$(foreach var, $(LIBS), $(MAKE) -C $(var) clean;)

fclean:
		$(foreach var, $(LIBS), $(MAKE) -C $(var) fclean;)

re:	fclean all

.PHONY:	all mklibs clean fclean