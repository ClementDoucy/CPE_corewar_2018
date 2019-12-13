/*
** EPITECH PROJECT, 2019
** src
** File description:
** strcats
*/

#include "mystring.h"

char *my_strcat(char *start, char const *end)
{
    size_t len = my_strlen(start);

    for (size_t i = 0; end[i]; i++)
        start[len + i] = end[i];
    return start;
}

char *my_strncat(char *start, char const *end, size_t n)
{
    size_t len = my_strlen(start);

    for (size_t i = 0; end[i] && i < n; i++)
        start[len + i] = end[i];
    return start;
}

char *my_strmerge(char *str1, char *str2)
{
    size_t lens = my_strlen(str1) + my_strlen(str2);
    char *merge = malloc(sizeof(char) * (lens + 1));

    if (!merge)
        return NULL;
    merge = my_strcpy(merge, str1);
    merge = my_strcat(merge, str2);
    merge[lens] = 0;
    return merge;
}

char *my_strmerge_plus(char *str1, char *str2, char *split)
{
    char *merge = my_strmerge(str1, split);
    char *plus = NULL;

    if (!merge)
        return NULL;
    if (str2 != NULL) {
        plus = my_strmerge(merge, str2);
        free(merge);
    } else {
        plus = merge;
    }
    return plus;
}