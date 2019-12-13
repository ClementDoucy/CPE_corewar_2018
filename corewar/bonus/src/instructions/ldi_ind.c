/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

static int ldi_ind_dir_reg(vm_t *vm, prog_t *prog)
{
    short int ind = 0;
    short int sum[2] = {0};
    int reg = 0;
    my_memcpy(&reg, &vm->mem[(prog->pc + 6) % MEM_SIZE], 1);
    if (is_reg_exist(reg) == false) {
        modify_carry(prog, false);
        return 84;
    }
    my_memcpy(&ind, &vm->mem[(prog->pc + 2) % MEM_SIZE], IND_SIZE);
    my_memcpy(&sum[0], &vm->mem[(prog->pc + 4) % MEM_SIZE], IND_SIZE);
    ind = convert_endian_number_short(ind);
    sum[0] = convert_endian_number_short(sum[0]);
    my_memcpy(&sum[1], &vm->mem[prog->pc + ind % IDX_MOD], IND_SIZE);
    sum[1] = convert_endian_number_short(sum[1]);
    my_memcpy(&prog->r[reg - 1], &vm->mem[prog->pc + \
            ((int)sum[0] + (int)sum[1]) % IDX_MOD], REG_SIZE);
    prog->r[reg - 1] = convert_endian_number(prog->r[reg - 1]);
    prog->pc = (prog->pc + 7) % MEM_SIZE;
    modify_carry(prog, true);
    return 0;
}

static int ldi_ind_reg_reg(vm_t *vm, prog_t *prog)
{
    int reg[2] = {0};
    short int i = 0;
    short int sum[2] = {0};
    my_memcpy(&i, &vm->mem[(prog->pc + 2) % MEM_SIZE], IND_SIZE);
    i = convert_endian_number_short(i);
    my_memcpy(&reg[0], &vm->mem[(prog->pc + 4) % MEM_SIZE], 1);
    my_memcpy(&reg[1], &vm->mem[(prog->pc + 5) % MEM_SIZE], 1);
    if (!is_reg_exist(reg[0]) || !is_reg_exist(reg[1])) {
        modify_carry(prog, false);
        return 84;
    }
    my_memcpy(&sum[0], &vm->mem[(prog->pc + i % IDX_MOD) % MEM_SIZE], IND_SIZE);
    sum[0] = convert_endian_number_short(sum[0]);
    my_memcpy(&sum[1], &prog->r[reg[0] - 1], IND_SIZE);
    my_memcpy(&prog->r[reg[1] - 1], &vm->mem[(prog->pc + \
                ((int)sum[0] + (int)sum[1]) % IDX_MOD) % MEM_SIZE], REG_SIZE);
    prog->r[reg[1] - 1] = convert_endian_number(prog->r[reg[1] - 1]);
    prog->pc = (prog->pc + 6) % MEM_SIZE;
    modify_carry(prog, true);
    return 0;
}

int ldi_ind_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3])
{
    if (arg[1] == T_DIR)
        return ldi_ind_dir_reg(vm, prog);
    if (arg[1] == T_REG)
        return ldi_ind_reg_reg(vm, prog);
    modify_carry(prog, false);
    return 84;
}
