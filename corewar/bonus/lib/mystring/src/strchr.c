/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** chr
*/

#include "mystring.h"

char *my_strchr(char *str, char c)
{
    for (size_t i = 0; str[i]; i++)
        if (str[i] == c)
            return (&(str[i]));
    return '\0';
}

char *my_strrchr(char *str, char c)
{
    for (size_t i = my_strlen(str); i > 0; i--)
        if (str[i] == c)
            return (&(str[i]));
    return '\0';
}

char *my_strrchrnul(char *str, char c)
{
    for (size_t i = my_strlen(str); i > 0; i--)
        if (str[i] == c)
            return (&(str[i]));
    return NULL;
}

char *my_strchrnul(char *str, char c)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            return (&(str[i]));
    return NULL;
}