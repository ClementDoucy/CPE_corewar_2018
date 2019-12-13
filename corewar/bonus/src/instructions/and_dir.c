/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

static int and_dir_reg_reg(vm_t *vm, prog_t *prog)
{
    int reg[2] = {0};
    int value_to_and = 0;

    my_memcpy(&reg[0], &vm->mem[(prog->pc + 6) % MEM_SIZE], 1);
    my_memcpy(&reg[1], &vm->mem[(prog->pc + 7) % MEM_SIZE], 1);
    if (!is_reg_exist(reg[0]) || !is_reg_exist(reg[1])) {
        modify_carry(prog, false);
        return 84;
    }
    my_memcpy(&value_to_and, &vm->mem[(prog->pc + 2) % MEM_SIZE], DIR_SIZE);
    value_to_and = convert_endian_number(value_to_and);
    prog->r[reg[1] - 1] = prog->r[reg[0] - 1] & value_to_and;
    prog->pc = (prog->pc + 8) % MEM_SIZE;
    modify_carry(prog, true);
    return 0;
}

static int and_dir_dir_reg(vm_t *vm, prog_t *prog)
{
    int reg = 0;
    int value_to_and[2] = {0};

    my_memcpy(&value_to_and[0], &vm->mem[(prog->pc + 2) % MEM_SIZE], DIR_SIZE);
    my_memcpy(&value_to_and[1], &vm->mem[(prog->pc + 6) % MEM_SIZE], DIR_SIZE);
    my_memcpy(&reg, &vm->mem[(prog->pc + 10) % MEM_SIZE], 1);
    if (!is_reg_exist(reg)) {
        modify_carry(prog, false);
        return 84;
    }
    value_to_and[0] = convert_endian_number(value_to_and[0]);
    value_to_and[1] = convert_endian_number(value_to_and[1]);
    prog->r[reg - 1] = value_to_and[0] & value_to_and[1];
    prog->pc = (prog->pc + 11) % MEM_SIZE;
    modify_carry(prog, true);
    return 0;
}

static int and_dir_ind_reg(vm_t *vm, prog_t *prog)
{
    int reg = 0;
    short int index = 0;
    int value_to_and[2] = {0};

    my_memcpy(&value_to_and[0], &vm->mem[(prog->pc + 2) % MEM_SIZE], DIR_SIZE);
    my_memcpy(&index, &vm->mem[(prog->pc + 6) % MEM_SIZE], IND_SIZE);
    my_memcpy(&reg, &vm->mem[(prog->pc + 8) % MEM_SIZE], 1);
    if (!is_reg_exist(reg)) {
        modify_carry(prog, false);
        return 84;
    }
    value_to_and[0] = convert_endian_number(value_to_and[0]);
    index = convert_endian_number_short(index);
    my_memcpy(&value_to_and[1], &vm->mem[(prog->pc + index) % MEM_SIZE], \
        DIR_SIZE);
    value_to_and[1] = convert_endian_number(value_to_and[1]);
    prog->r[reg - 1] = value_to_and[0] & value_to_and[1];
    prog->pc = (prog->pc +  9) % MEM_SIZE;
    modify_carry(prog, true);
    return 0;
}

int and_dir_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3])
{
    if (arg[1] == T_REG)
        return and_dir_reg_reg(vm, prog);
    if (arg[1] == T_DIR)
        return and_dir_dir_reg(vm, prog);
    if (arg[1] == T_IND)
        return and_dir_ind_reg(vm, prog);
    modify_carry(prog, false);
    return 84;
}
