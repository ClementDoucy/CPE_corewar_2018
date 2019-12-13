/*
** EPITECH PROJECT, 2019
** tools_2.c
** File description:
** contains basic functions
*/

#include "tools.h"

void my_puts_stderr(char *str)
{
    if (!str)
        return;
    for (int i = 0; str[i] != '\0'; i++)
        write(2, &str[i], 1);
    write(2, "\n", 1);
}

void destroy_2d_tab(void **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

void my_putstr(char *str)
{
    if (!str)
        return;
    for (int i = 0; str[i] != '\0'; i++)
        write(1, &str[i], 1);
}

void my_putstr_stderr(const char *str)
{
    if (!str)
        return;
    for (int i = 0; str[i] != '\0'; i++)
        write(2, &str[i], 1);
}

bool are_eq_str(char *s1, char *s2)
{
    if (!s1 || !s2)
        return false;
    if (my_strlen(s1) != my_strlen(s2))
        return false;
    for (int i = 0; s1[i] != '\0'; i++)
        if (s1[i] != s2[i])
            return false;
    return true;
}
