/*
** EPITECH PROJECT, 2019
** src
** File description:
** str_1
*/

#include "mystring.h"

void *my_memset(char *str, char fill, size_t n)
{
    for (size_t i = 0; i < n; i++)
        str[i] = fill;
    return str;
}

void *my_memcpy(void *dest, void *src, size_t nb)
{
    for (size_t i = 0; i < nb; i++)
        ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
    return dest;
}
