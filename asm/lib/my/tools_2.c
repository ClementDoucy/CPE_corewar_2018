/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** contains basic functions
*/

#include "tools.h"

void my_puts(char *str)
{
    if (!str)
        return;
    for (int i = 0; str[i] != '\0'; i++)
        write(1, &str[i], 1);
    write(1, "\n", 1);
}

char *my_strcat(char *dest, char *src)
{
    size_t size = my_strlen(dest) + my_strlen(src) + 1;
    char *new = malloc(sizeof(char) * size);
    int i = 0;

    if (!new)
        return NULL;
    if (dest)
        for (; dest[i] != '\0'; i++)
            new[i] = dest[i];
    if (src)
        for (int k = 0; src[k] != '\0'; k++) {
            new[i] = src[k];
            i++;
        }
    new[i] = '\0';
    return new;
}

void my_put_2d_str(char **map)
{
    if (!map)
        return;
    for (int i = 0; map[i]; i++) {
        if (!map[i])
            return;
        my_puts(map[i]);
    }
}

int my_getnbr(char *str)
{
    int a = 0;
    int n = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            if (i != 0 && str[i - 1] == '-')
                n = 1;
            if (str[i + 1] < 48 || str[i + 1] > 57) {
                a = a + str[i] - 48;
                if (n == 1)
                    return (-a);
                return (a);
            }
            a = a * 10 + (str[i] - 48) * 10;
        }
    }
    return (a);
}
