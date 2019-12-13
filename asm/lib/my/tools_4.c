/*
** EPITECH PROJECT, 2019
** tools_3.c
** File description:
** contains generic function
*/

#include "tools.h"

void print_2d_str(char **str)
{
    if (!str)
        return;
    for (int i = 0; str[i]; i++)
        my_puts(str[i]);
}

char **realloc_2d_str(char **str, size_t size)
{
    char **new = NULL;
    size_t new_size = str_2d_len(str);
    int k = 0;

    new_size = new_size + size;
    if (!(new = malloc(sizeof(char *) * new_size)))
        return NULL;
    for (; str[k]; k++)
        new[k] = my_strdup(str[k]);
    new[(int)new_size - 1] = NULL;
    destroy_2d_tab((void **)str);
    return new;
}

size_t str_2d_len(char **str)
{
    size_t size = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++)
        size++;
    return size + 1;
}

char **str_2d_dup(char **str)
{
    char **new = NULL;
    size_t size = str_2d_len(str);
    int i = 0;

    if (!size)
        return NULL;
    if (!(new = malloc(sizeof(char *) * size)))
        return NULL;
    for (; str[i]; i++)
        new[i] = my_strdup(str[i]);
    new[i] = NULL;
    return new;
}
