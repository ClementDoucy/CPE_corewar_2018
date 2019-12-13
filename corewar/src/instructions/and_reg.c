/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

static int and_reg_reg_reg(vm_t *vm, prog_t *prog)
{
    int reg[3] = {0};

    for (int i = 0; i < 3; i++) {
        my_memcpy(&reg[i], &vm->mem[(prog->pc + (i + 2)) % MEM_SIZE], 1);
        if (!is_reg_exist(reg[i])) {
            modify_carry(prog, false);
            return 84;
        }
    }
    prog->r[reg[2] - 1] = prog->r[reg[0] - 1] & prog->r[reg[1] - 1];
    prog->pc = (prog->pc + 5) % MEM_SIZE;
    modify_carry(prog, true);
    return 0;
}

static int and_reg_dir_reg(vm_t *vm, prog_t *prog)
{
    int reg[2] = {0};
    int value_to_and = 0;

    my_memcpy(&reg[0], &vm->mem[(prog->pc + 2) % MEM_SIZE], 1);
    my_memcpy(&reg[1], &vm->mem[(prog->pc + 7) % MEM_SIZE], 1);
    if (!is_reg_exist(reg[0]) || !is_reg_exist(reg[1])) {
        modify_carry(prog, false);
        return 84;
    }
    my_memcpy(&value_to_and, &vm->mem[(prog->pc + 3) % MEM_SIZE], DIR_SIZE);
    value_to_and = convert_endian_number(value_to_and);
    prog->r[reg[1] - 1] = prog->r[reg[0] - 1] & value_to_and;
    prog->pc = (prog->pc + 8) % MEM_SIZE;
    modify_carry(prog, true);
    return 0;
}

static int and_reg_ind_reg(vm_t *vm, prog_t *prog)
{
    int reg[2] = {0};
    short int index = 0;
    int value_to_and = 0;

    my_memcpy(&reg[0], &vm->mem[(prog->pc + 2) % MEM_SIZE], 1);
    my_memcpy(&reg[1], &vm->mem[(prog->pc + 5) % MEM_SIZE], 1);
    if (!is_reg_exist(reg[0]) || !is_reg_exist(reg[1])) {
        modify_carry(prog, false);
        return 84;
    }
    my_memcpy(&index, &vm->mem[(prog->pc + 3) % MEM_SIZE], IND_SIZE);
    index = convert_endian_number_short(index);
    my_memcpy(&value_to_and, &vm->mem[(prog->pc + index) % MEM_SIZE], DIR_SIZE);
    value_to_and = convert_endian_number(value_to_and);
    prog->r[reg[1] - 1] = prog->r[reg[0] - 1] & value_to_and;
    prog->pc = (prog->pc + 6) % MEM_SIZE;
    modify_carry(prog, true);
    return 0;
}

int and_reg_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3])
{
    if (arg[1] == T_REG)
        return and_reg_reg_reg(vm, prog);
    if (arg[1] == T_DIR)
        return and_reg_dir_reg(vm, prog);
    if (arg[1] == T_IND)
        return and_reg_ind_reg(vm, prog);
    modify_carry(prog, false);
    return 84;
}
