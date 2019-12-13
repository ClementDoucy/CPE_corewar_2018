/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

int sti(vm_t *vm, prog_t *prog)
{
    unsigned char coding_byte = vm->mem[(prog->pc + 1) % MEM_SIZE];
    args_type_t arg[3] = {0};

    for (int i = 0; i < 3; i++)
        arg[i] = get_arg_type(coding_byte, i + 1);
    if (arg[0] != T_REG)
        return 84;
    if (arg[1] == T_REG)
        return sti_reg_reg_all(vm, prog, arg);
    if (arg[1] == T_DIR)
        return sti_reg_dir_all(vm, prog, arg);
    if (arg[1] == T_IND)
        return sti_reg_ind_all(vm, prog, arg);
    return 84;
}
