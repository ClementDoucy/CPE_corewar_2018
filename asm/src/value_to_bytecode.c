/*
** EPITECH PROJECT, 2019
** value_to_bytecode.c
** File description:
** convert arugments value into bytecode
*/

#include <unistd.h>
#include "tools.h"
#include "asm.h"

bool write_register(int bin, void *value, size_t *current_os)
{
    char *reg = value;

    if (write(bin, reg, sizeof(char)) == -1)
        return false;
    *current_os += sizeof(char);
    return true;
}

bool write_direct(int bin, void *value, size_t *current_os)
{
    int *dir= value;

    *dir = convert_endian_number(*dir);
    if (write(bin, dir, sizeof(int)) == -1)
        return false;
    *current_os += sizeof(int);
    return true;
}

bool write_indirect(int bin, void *value, size_t *current_os)
{
    short *ind = value;

    *ind = convert_endian_number_short(*ind);
    if (write(bin, ind, sizeof(short)) == -1)
        return false;
    *current_os += sizeof(short);
    return true;
}

bool write_direct_label(
    int bin, void *value, size_t *offset, labelizer_t *labels)
{
    int dir = 0;
    int i = 0;

    for (; labels[i].label; i++)
        if (are_eq_str((char *)value, labels[i].label)) {
            dir = (int)labels[i].offset - (int)offset[0] - 1;
            break;
        }
    if (!labels[i].label)
        return true;
    dir = convert_endian_number(dir);
    if (write(bin, &dir, sizeof(int)) == -1)
        return false;
    offset[1] += sizeof(int);
    return true;
}

bool write_indirect_label(
    int bin, void *value, size_t *offset, labelizer_t *labels)
{
    short ind = 0;
    int i = 0;

    for (; labels[i].label; i++)
        if (are_eq_str((char *)value, labels[i].label)) {
            ind = (short)labels[i].offset - (short)offset[0] - 1;
            break;
        }
    if (!labels[i].label)
        return true;
    ind = convert_endian_number_short(ind);
    if (write(bin, &ind, sizeof(short)) == -1)
        return false;
    offset[1] += sizeof(short);
    return true;
}
