/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** char
*/

#include "mystring.h"

int char_in(char c, char const *is_in)
{
    for (size_t i = 0; is_in[i]; i++)
        if (c == is_in[i])
            return true;
    return false;
}

int is_alpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return true;
    return false;
}

int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

int is_alpha_numeric(char c)
{
    if (is_digit(c) || is_alpha(c))
        return true;
    return false;
}

int is_space(char c)
{
    if (c == ' ')
        return true;
    return false;
}