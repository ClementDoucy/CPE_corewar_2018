/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** convert
*/

#include "mystring.h"
#include "../../../include/op.h"

static int error(void)
{
    write (2, "invalid number in 'my_hexa_to_dec' function\n", 34);
    return -84;
}

int my_hexa_to_dec(char *n)
{
    int dec = 0;
    int power = 1;

    if (my_strncmp(n, "0x", 2) || my_strlen(n) > 16)
        return error();
    n = my_revstr(n);
    n[my_strlen(n) - 2] = 0;
    for (int i = 0; n[i]; i++) {
        if (!char_in(n[i], "0123456789abcdefABCDEF"))
            return error();
        if (is_digit(n[i]))
            dec += ((n[i] - 48) * power);
        if (n[i] >= 'A' && n[i] <= 'F')
            dec += ((n[i] - 'A' + 10) * power);
        if (n[i] >= 'a' && n[i] <= 'f')
            dec += ((n[i] - 'a' + 10) * power);
        power *= 16;
    }
    return dec;
}

unsigned int convert_endian_number(unsigned int nb)
{
    unsigned int new = 0;
    unsigned int byte_1 = (nb & 0x000000ff) << 24;
    unsigned int byte_2 = (nb & 0x0000ff00) << 8;
    unsigned int byte_3 = (nb & 0x00ff0000) >> 8;
    unsigned int byte_4 = (nb & 0xff000000) >> 24;

    new = byte_1 | byte_2 | byte_3 | byte_4;
    return new;
}

unsigned short int convert_endian_number_short(unsigned short int nb)
{
    unsigned short int new = 0;
    unsigned short int byte_1 = (nb & 0x00ff) << 8;
    unsigned short int byte_2 = (nb & 0xff00) >> 8;

    new = byte_1 | byte_2;
    return new;
}
