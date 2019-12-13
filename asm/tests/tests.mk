##
## EPITECH PROJECT, 2019
## tests.mk
## File description:
## sources for unit test
##

include ../src/sources.mk

SRCDIR	=	./../src

SRCTEST	+=	./tests.c
SRCTEST	+=	./usage_tests.c
SRCTEST	+=	./bytecode_tests.c
SRCTEST	+=	./parsing_tests.c
SRCTEST +=	./pre_parse_test.c
SRCTEST	+=	./error_handling_tests.c
SRCTEST +=	$(SRCS)
