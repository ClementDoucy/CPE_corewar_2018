/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

static int lld_dir_reg(vm_t *vm, prog_t *prog)
{
    int dir1 = 0;
    int reg2 = 0;

    my_memcpy(&dir1, &(vm->mem[(prog->pc + 2) % MEM_SIZE]), sizeof(int));
    dir1 = convert_endian_number(dir1);
    my_memcpy(&reg2, &(vm->mem[(prog->pc + 6) % MEM_SIZE]), 1);
    if (is_reg_exist(reg2) == false) {
        modify_carry(prog, false);
        return 84;
    }
    prog->r[reg2 - 1] = dir1;
    modify_carry(prog, true);
    prog->pc = (prog->pc + 7) % MEM_SIZE;
    return 0;
}

static int lld_ind_reg(vm_t *vm, prog_t *prog)
{
    short int ind1 = 0;
    int reg2 = 0;
    int value_to_load = 0;

    my_memcpy(&ind1, &(vm->mem[(prog->pc + 2) % MEM_SIZE]), sizeof(short int));
    ind1 = convert_endian_number_short(ind1);
    my_memcpy(&value_to_load, &vm->mem[(prog->pc + ind1) % MEM_SIZE], REG_SIZE);
    value_to_load = convert_endian_number(value_to_load);
    my_memcpy(&reg2, &(vm->mem[(prog->pc + 4) % MEM_SIZE]), 1);
    if (is_reg_exist(reg2) == false) {
        modify_carry(prog, false);
        return 84;
    }
    prog->r[reg2 - 1] = value_to_load;
    modify_carry(prog, true);
    prog->pc = (prog->pc + 5) % MEM_SIZE;
    return 0;
}

int lld(vm_t *vm, prog_t *prog)
{
    unsigned char coding_byte = vm->mem[(prog->pc + 1) % MEM_SIZE];
    args_type_t arg[2] = {0};

    if (coding_byte != 0x90 && coding_byte != 0xd0) {
        modify_carry(prog, false);
        return 84;
    }
    for (int i = 0; i < 2; i++)
        arg[i] = get_arg_type(coding_byte, i + 1);
    if (arg[0] == T_DIR)
        return lld_dir_reg(vm, prog);
    else if (arg[0] == T_IND)
        return lld_ind_reg(vm, prog);
    modify_carry(prog, false);
    return 84;
}
