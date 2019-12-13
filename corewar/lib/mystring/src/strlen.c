/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** strlen
*/

#include "mystring.h"

size_t my_strlen(char const *str)
{
    size_t len = 0;

    for (; str && str[len]; len++);
    return len;
}

size_t my_strlen_stop(char const *str, char stop)
{
    size_t len = 0;

    for (; str[len] != '\0' && str[len] != stop; len++);
    return len;
}

size_t my_strcountw(char *str, char *delims)
{
    size_t words = 0;

    for (size_t i = 0; str[i];) {
        for (;str[i] && char_in(str[i], delims) == true; i++);
        if (str[i])
            words++;
        for (; str[i] && char_in(str[i], delims) == false; i++);
    }
    return words;
}

size_t my_nstrcountw(char *str)
{
    size_t words = 0;

    for (size_t i = 0; str[i]; i++) {
        if (!char_in(str[i], " \t\n"))
            words++;
        for (; !char_in(str[i], " \t\n"); i++);
    }
    return words;
}
