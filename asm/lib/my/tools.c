/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** contains basic functions
*/

#include "tools.h"

char *my_strdup(char *src)
{
    size_t size = 0;
    char *str = NULL;

    if (!src)
        return NULL;
    for (int k = 0; src[k] != '\0'; k++)
        size++;
    str = malloc(sizeof(char) * (size + 1));
    if (!str)
        return NULL;
    for (int i = 0; src[i] != '\0'; i++)
        str[i] = src[i];
    str[(int)size] = '\0';
    return str;
}

size_t my_strlen(const char *str)
{
    size_t size = 0;
    int i = 0;

    if (!str)
        return size;
    for (; str[i] != '\0'; i++);
    size = i;
    return size;
}

char *my_strcat_wmlc(char *dest, char *src, int i)
{
    if (src)
        for (int k = 0; src[k] != '\0'; k++) {
            dest[i] = src[k];
            i++;
        }
    dest[i] = '\0';
    return dest;
}
