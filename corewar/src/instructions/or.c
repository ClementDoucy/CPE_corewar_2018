/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

int or(vm_t *vm, prog_t *prog)
{
    unsigned char coding_byte = vm->mem[(prog->pc + 1) % MEM_SIZE];
    args_type_t arg[3] = {0};

    for (int i = 0; i < 3; i++)
        arg[i] = get_arg_type(coding_byte, i + 1);
    if (arg[2] != T_REG) {
        modify_carry(prog, false);
        return 84;
    }
    if (arg[0] == T_REG)
        return or_reg_all_reg(vm, prog, arg);
    if (arg[0] == T_DIR)
        return or_dir_all_reg(vm, prog, arg);
    if (arg[0] == T_IND)
        return or_ind_all_reg(vm, prog, arg);
    modify_carry(prog, false);
    return 84;
}
