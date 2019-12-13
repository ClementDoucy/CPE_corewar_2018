/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** strepur
*/

#include "mystring.h"

static int not_ended_str__(char const *str, char *rm)
{
    for (int i = 0; str[i]; i++)
        if (!char_in(str[i], rm))
            return 1;
    return 0;
}

static int getlen_epured__(char const *str, char *rm)
{
    int i = 0;
    int len = 0;

    for (; char_in(str[i], rm); i++);
    for (; not_ended_str__(&(str[i]), rm); i++) {
        len++;
        if (char_in(str[i], rm)) {
            len++;
            for (; char_in(str[i], rm); i++);
        }
    }
    return len;
}

static void epure_cpy__(char const *str, char **epured, char *rm)
{
    int i = 0;
    int j = 0;

    for (; char_in(str[i], rm); i++);
    for (; not_ended_str__(&(str[i]), rm); i++) {
        if (char_in(str[i], rm)) {
            (*epured)[j++] = str[i];
            for (; char_in(str[i], rm); i++);
        }
        if (!char_in(str[i], rm))
            (*epured)[j++] = str[i];
    }
}

char *my_strepure(char const *str, char *rm)
{
    int lenstr = getlen_epured__(str, rm);
    char *epured = malloc(sizeof(char) * lenstr + 1);

    if (!epured)
        return NULL;
    epure_cpy__(str, &epured, rm);
    epured[lenstr] = 0;
    return epured;
}