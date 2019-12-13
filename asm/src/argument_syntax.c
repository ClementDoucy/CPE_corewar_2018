/*
** EPITECH PROJECT, 2019
** argument_syntax.c
** File description:
** check argument syntax
*/

#include "tools.h"
#include "asm.h"

bool is_valid_reg(char *arg)
{
    int nb = 0;

    if (!arg || *arg != 'r' || !is_integer(arg + 1)) {
        put_error("Invalid register argument.");
        return false;
    }
    nb = my_getnbr(arg + 1);
    if (nb < 1 || nb > 16) {
        put_error("Invalid register argument.");
        return false;
    }
    return true;
}

bool is_valid_dir(char *arg)
{
    if (!arg || *arg != '%' || !*(arg + 1) || !is_integer(arg + 1)) {
        put_error("Invalid direct argument.");
        return false;
    }
    return true;
}

bool is_valid_ind(char *arg)
{
    if (!arg || !is_integer(arg)) {
        put_error("Invalid indirect argument.");
        return false;
    }
    return true;
}

bool is_valid_dir_lab(char *arg)
{
    if (!arg || *arg != '%' || *(arg + 1) != ':') {
        put_error("Invalid direct label call.");
        return false;
    }
    return true;
}

bool is_valid_ind_lab(char *arg)
{
    if (!arg || *arg != ':') {
        put_error("Invalid indirect label call.");
        return false;
    }
    return true;
}
