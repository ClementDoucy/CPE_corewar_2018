/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** arrlen
*/

#include "mystring.h"

size_t my_arrlen(char **arr)
{
    size_t len = 0;

    for (; arr[len] != NULL; len++);
    return len;
}