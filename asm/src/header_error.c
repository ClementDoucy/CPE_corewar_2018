/*
** EPITECH PROJECT, 2019
** header_error.c
** File description:
** check error in header
*/

#include "asm.h"

static bool check_quote_error(const char *line, size_t max_size)
{
    int nb_quote = 0;
    int i = 0;
    size_t size = 0;

    for (; line[i] && nb_quote != 2; i++) {
        if (nb_quote == 1 && line[i] != '"')
            size++;
        if (line[i] == '"')
            nb_quote++;
    }
    i--;
    if (nb_quote != 2 || line[i + 1]) {
        put_error("Syntax.");
        return true;
    }
    if (size > max_size) {
        put_error("To long string.");
        return true;
    }
    return false;
}

bool check_h_name_err(const char *line, h_error_t *h_error)
{
    for (int i = 5; line[i] && line[i] != '"'; i++)
        if (line[i] != ' ') {
            put_error("Invalid instruction.");
            return true;
        }
    if (h_error->name_catch) {
        put_error("Name already defined.");
        return true;
    }
    return check_quote_error(line, PROG_NAME_LENGTH);
}

bool check_h_com_err(const char *line, h_error_t *h_error)
{
    for (int i = 8; line[i] && line[i] != '"'; i++)
        if (line[i] != ' ') {
            put_error("Invalid instruction.");
            return true;
        }
    if (h_error->comment_catch) {
        put_error("Prog comment already defined.");
        return true;
    } if (!h_error->prev_was_name) {
        put_error("Prog comment must be just after prog name.");
        return true;
    }
    return check_quote_error(line, COMMENT_LENGTH);
}
