/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

static int st_reg1_to_reg2(vm_t *vm, prog_t *prog, int reg1)
{
    int reg2 = 0;

    my_memcpy(&reg2, &vm->mem[(prog->pc + 3) % MEM_SIZE], 1);
    if (is_reg_exist(reg2) == false)
        return 84;
    prog->r[reg2 - 1] = prog->r[reg1 - 1];
    prog->pc = (prog->pc + 4) % MEM_SIZE;
    return 0;
}

static int st_reg1_to_ind2(vm_t *vm, prog_t *prog, int reg1)
{
    short int ind2 = 0;
    int value_to_store = 0;

    my_memcpy(&ind2, &vm->mem[(prog->pc + 3) % MEM_SIZE], IND_SIZE);
    ind2 = convert_endian_number_short(ind2);
    value_to_store = convert_endian_number(prog->r[reg1 - 1]);
    my_memcpy(&vm->mem[(prog->pc + ind2 % IDX_MOD) % MEM_SIZE], \
            &value_to_store, sizeof(int));
    prog->pc = (prog->pc + 5) % MEM_SIZE;
    return 0;
}

int st(vm_t *vm, prog_t *prog)
{
    unsigned char coding_byte = vm->mem[(prog->pc + 1) % MEM_SIZE];
    args_type_t arg[2] = {0};
    int reg1 = 0;

    if (coding_byte != 0x50 && coding_byte != 0x70)
        return 84;
    for (int i = 0; i < 2; i++)
        arg[i] = get_arg_type(coding_byte, i + 1);
    my_memcpy(&reg1, &vm->mem[(prog->pc + 2) % MEM_SIZE], 1);
    if (is_reg_exist(reg1) == false)
        return 84;
    if (arg[1] == T_REG)
        return st_reg1_to_reg2(vm, prog, reg1);
    else if (arg[1] == T_IND)
        return st_reg1_to_ind2(vm, prog, reg1);
    return 84;
}
