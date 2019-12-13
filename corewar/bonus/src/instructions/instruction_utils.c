/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"

int get_arg_type(unsigned char coding_byte, int param_index)
{
    int type = 0;

    if (param_index == 1)
        type = (coding_byte & 0b11000000) >> 6;
    if (param_index == 2)
        type = (coding_byte & 0b00110000) >> 4;
    if (param_index == 3)
        type = (coding_byte & 0b00001100) >> 2;
    if (param_index == 4)
        type = (coding_byte & 0b00000011);
    if (type == 0b00000001)
        return T_REG;
    if (type == 0b00000010)
        return T_DIR;
    if (type == 0b00000011)
        return T_IND;
    return 84;
}

int modify_carry(prog_t *prog, const bool on)
{
    if (on == true)
        prog->carry = true;
    else
        prog->carry = false;
    return 0;
}

bool is_reg_exist(const int reg)
{
    if (reg < 1 || reg > REG_NUMBER)
        return false;
    return true;
}
