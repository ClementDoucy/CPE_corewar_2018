/*
** EPITECH PROJECT, 2019
** int_to_str
** File description:
** convert int into string
*/

#include "my_print.h"

size_t len_int(int nb)
{
    size_t size = 1;

    if (nb < 0)
        size++;
    while (nb > 9 || nb < -9) {
        size++;
        nb = nb / 10;
    }
    return size;
}

char *int_to_str(int nb)
{
    char *str = NULL;
    int i = 0;
    size_t size = len_int(nb);

    if (!(str = malloc(sizeof(char) * (size + 1))))
        return NULL;
    if (nb < 0) {
        i++;
        str[0] = '-';
        nb = -nb;
    }
    str = fill_str(i, size, nb, str);
    return str;
}

int compute_div(int nb)
{
    int div = 1;

    for (; nb > 9 || nb < -9; div *= 10)
        nb /= 10;
    return div;
}

char *fill_str(int i, size_t size, int nb, char *str)
{
    int div = compute_div(nb);
    int save = 0;

    for (; i < (int)size; i++) {
        save = nb;
        nb /= div;
        str[i] = nb + 48;
        nb = save % div;
        div /= 10;
    }
    str[size] = '\0';
    return str;
}
