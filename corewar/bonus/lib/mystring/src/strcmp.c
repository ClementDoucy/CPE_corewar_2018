/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** strcmp
*/

#include "mystring.h"

int is_same_str(const char *str1, const char *str2)
{
    if (!str1 || !str2)
        return 0;
    if (my_strlen(str1) != my_strlen(str2))
        return 0;
    for (int i = 0; str1[i] && str2[i]; i++)
        if (str1[i] != str2[i])
            return 0;
    return 1;
}

int is_same_str_stop(const char *str1, const char *str2, char stop)
{
    int i;

    if (!str1 || !str2)
        return 0;
    for (i = 0; str1[i] && str2[i] &&
        str1[i] != stop && str2[i] != stop; i++) {
        if (str1[i] != str2[i])
            return 0;
    }
    return str1[i] == stop && str2[i] == '\0';
}

int my_strcmp(const char *str1, const char *str2)
{
    size_t i = 0;

    for (; str1[i] && str2[i]; i++) {
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
    }
    return str1[i] - str2[i];
}

int my_strncmp(const char *a, const char *b, size_t n)
{
    size_t i = 0;

    while (a[i] && b[i] && i < n) {
        if (a[i] > b[i])
            return 1;
        if (a[i] < b[i])
            return -1;
        i++;
    }
    return 0;
}
