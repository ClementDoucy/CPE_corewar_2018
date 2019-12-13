/*
** EPITECH PROJECT, 2019
** error_message.c
** File description:
** print error message
*/

#include "tools.h"

static const char *red = "\x1b[31m";
static const char *magenta = "\x1b[35m";
static const char *reset = "\x1b[0m";
static const char *bold_on = "\e[1m";
static const char *bold_off = "\e[0m";

int put_error(const char *msg)
{
    if (msg) {
        my_putstr_stderr(bold_on);
        my_putstr_stderr(red);
        my_putstr_stderr("Error:");
        my_putstr_stderr(reset);
        my_putstr_stderr(bold_off);
        write(2, " ", 1);
        my_putstr_stderr(msg);
        write(2, "\n", 1);
    }
    return 84;
}

void put_warning(const char *msg)
{
    if (!msg)
        return;
    my_putstr_stderr(bold_on);
    my_putstr_stderr(magenta);
    my_putstr_stderr("Warning:");
    my_putstr_stderr(reset);
    my_putstr_stderr(bold_off);
    write(2, " ", 1);
    my_putstr_stderr(msg);
    write(2, "\n", 1);
}
