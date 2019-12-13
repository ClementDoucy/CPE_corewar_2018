/*
** EPITECH PROJECT, 2019
** str_clean.c
** File description:
** functions to clean str
*/

#include "tools.h"

char *str_clean(char *str)
{
    char *new = NULL;
    int i = 0;
    int k = 0;
    bool quote = false;

    if (!str || !(new = malloc(sizeof(char) * (my_strlen(str) + 1))))
        return NULL;
    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i]; i++) {
        quote = (str[i] == '"' ? !quote : quote);
        if (quote)
            new[k++] = str[i];
        if (!quote && str[i] != ' ' && str[i] != '\t')
            new[k++] = str[i];
        if (!quote && str[i + 1] && (str[i] == ' ' || str[i] == '\t')
            && str[i + 1] != ' ' && str[i + 1] != '\t')
            new[k++] = ' ';
    }
    new[k] = '\0';
    return new;
}

void remove_comment(char *str)
{
    bool quote = false;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '"')
            quote = !quote;
        if (!quote && str[i] == '#') {
            str[i] = '\0';
            return;
        }
    }
}
