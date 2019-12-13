/*
** EPITECH PROJECT, 2019
** init_functions.c
** File description:
** functions to init
*/

#include <stdlib.h>
#include "asm.h"

parser_t *init_parser(void)
{
    parser_t *parser = malloc(sizeof(parser_t));

    if (!parser) {
        put_error("malloc failed.");
        return NULL;
    }
    parser->h_error.name_catch = false;
    parser->h_error.comment_catch = false;
    parser->h_error.prev_was_name = false;
    parser->header.magic = COREWAR_EXEC_MAGIC;
    parser->header.prog_size = 0;
    for (int i = 0; i < PROG_NAME_LENGTH; i++)
        parser->header.prog_name[i] = '\0';
    for (int i = 0; i < COMMENT_LENGTH; i++)
        parser->header.comment[i] = '\0';
    parser->head = NULL;
    parser->labels = NULL;
    return parser;
}
