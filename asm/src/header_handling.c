/*
** EPITECH PROJECT, 2019
** header_handling.c
** File description:
** handle prog header
*/

#include "asm.h"

static bool get_string(const char *line, char *buf)
{
    int i = 0;
    int k = 0;

    for (; line[i] && line[i] != '"'; i++);
    if (!line[i])
        return false;
    i++;
    for (; line[i] && line[i] != '"'; k++, i++)
        buf[k] = line[i];
    if (!line[i])
        return false;
    buf[k] = '\0';
    return true;
}

bool handle_header_name(
    const char *line, header_t *header, h_error_t *h_error)
{
    if (check_h_name_err(line, h_error))
        return false;
    if (!get_string(line, header->prog_name))
        return false;
    h_error->name_catch = true;
    h_error->prev_was_name = true;
    return true;
}

bool handle_header_comment(const char *line, header_t *header,
    h_error_t *h_error)
{
    if (check_h_com_err(line, h_error))
        return false;
    if (!get_string(line, header->comment))
        return false;
    h_error->comment_catch = true;
    h_error->prev_was_name = false;
    return true;
}
