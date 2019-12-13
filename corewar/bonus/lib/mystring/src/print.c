/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** print
*/

#include "mystring.h"

int my_putchar(int std, char c)
{
    if (write(std, &c, 1) == -1)
        return -1;
    return 0;
}

int my_putstr(int std, const char *str)
{
    size_t len = my_strlen(str);

    if (write(std, str, len) == -1)
        return -1;
    return 0;
}

int my_putarr(int std, char **arr)
{
    for (size_t i = 0; arr[i]; i++) {
        if (my_putstr(std, arr[i]) == -1 || my_putchar(std, '\n'))
            return -1;
    }
    return 0;
}