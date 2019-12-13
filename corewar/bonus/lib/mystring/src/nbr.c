/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** nbr
*/

#include <mystring.h>

int is_str_int(char *str)
{
    int i = 0;

    if (!str)
        return 0;
    if (str[0] == '-' && is_digit(str[1]))
        i++;
    for (; str[i]; i++)
        if (!is_digit(str[i]))
            return false;
    return true;
}

int is_str_float(char *str)
{
    int i = 0;

    if (!str)
        return 0;
    if (str[0] == '-' && is_digit(str[1]))
        i++;
    for (; str[i] && str[i] != '.'; i++)
        if (!is_digit(str[i]))
            return false;
    if (!i)
        return 0;
    (str[i] == '.' && str[i + 1] != 0) ? (i++) : (i);
    for (; str[i]; i++)
        if (!is_digit(str[i]))
            return false;
    return true;
}