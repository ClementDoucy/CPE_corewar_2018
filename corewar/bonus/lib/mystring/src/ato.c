/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** ato
*/

#include "mystring.h"

int my_atoi(char *n)
{
    int b = 0;
    int i;

    for ((n[0] == '-') ? (i = 1) : (i = 0); n[i] && is_digit(n[i]); i++)
        (n[0] == '-') ? (b = b * 10 - (n[i] - 48)) : (b = b * 10 + n[i] - 48);
    return b;
}

float my_atof(char *n)
{
    float b = 0;
    int i;

    for ((n[0] == '-') ? (i = 1) : (i = 0); n[i] && n[i] != '.'; i++)
        (n[0] == '-') ? (b = b * 10 - (n[i] - 48)) : (b = b * 10 + n[i] - 48);
    (n[i] == '.') ? (i += 1) : (i);
    for (int j = 10; n[i]; j *= 10, i++)
        (n[0] == '-') ? (b -= (n[i] - 48.0) / j) : (b += (n[i] - 48.0) / j);
    return b;
}

double my_atod(char *n)
{
    double b = 0;
    int i;

    for ((n[0] == '-') ? (i = 1) : (i = 0); n[i] && n[i] != '.'; i++)
        (n[0] == '-') ? (b = b * 10 - (n[i] - 48)) : (b = b * 10 + n[i] - 48);
    (n[i] == '.') ? (i += 1) : (i);
    for (int j = 10; n[i]; j *= 10, i++)
        (n[0] == '-') ? (b -= (n[i] - 48.0) / j) : (b += (n[i] - 48.0) / j);
    return b;
}