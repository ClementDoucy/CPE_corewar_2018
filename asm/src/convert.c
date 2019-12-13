/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** convert
*/

#include "op.h"

int convert_endian_number(int nb)
{
    int new = 0;
    int byte_1 = (nb & 0x000000ff) << 24;
    int byte_2 = (nb & 0x0000ff00) << 8;
    int byte_3 = (nb & 0x00ff0000) >> 8;
    int byte_4 = (nb & 0xff000000) >> 24;

    new = byte_1 | byte_2 | byte_3 | byte_4;
    return new;
}

short int convert_endian_number_short(short int nb)
{
    short int new = 0;
    short int byte_1 = (nb & 0x00ff) << 8;
    short int byte_2 = (nb & 0xff00) >> 8;

    new = byte_1 | byte_2;
    return new;
}
