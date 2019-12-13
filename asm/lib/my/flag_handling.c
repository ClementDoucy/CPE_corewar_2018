/*
** EPITECH PROJECT, 2019
** flag_handling.c
** File description:
** manage flag
*/

#include "my_print.h"

bool detect_flag(const char *str)
{
    if (str[0] == '%' && (str[1] == 's' || str[1] == 'd'))
        return true;
    return false;
}

size_t len_param(char flag, va_list list)
{
    size_t size = 0;

    if (flag == 's')
        size = my_strlen(va_arg(list, char *));
    else
        size = len_int(va_arg(list, int));
    return size;
}
