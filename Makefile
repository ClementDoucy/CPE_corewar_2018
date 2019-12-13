##
## EPITECH PROJECT, 2019
## CPE_corewar_2018
## File description:
## Makefile
##

MKFILES	+=	./asm
MKFILES	+=	./corewar

all:
		$(foreach var, $(MKFILES), $(MAKE) -C $(var);)

clean:
		$(foreach var, $(MKFILES), $(MAKE) -C $(var) clean;)

fclean:
		$(foreach var, $(MKFILES), $(MAKE) -C $(var) fclean;)

tests_run:
		$(foreach var, $(MKFILES), $(MAKE) -C $(var) tests_run;)

re:	fclean all

.PHONY:	all clean fclean re tests_run
