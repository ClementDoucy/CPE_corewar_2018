/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** arr
*/

#include "mystring.h"

char *my_revstr(char *str)
{
    size_t i = 0;
    char tmp;

    while (i < my_strlen(str) / 2) {
        tmp = str[i];
        str[i] = str[my_strlen(str) - i - 1];
        str[my_strlen(str) - i - 1] = tmp;
        i++;
    }
    return str;
}
