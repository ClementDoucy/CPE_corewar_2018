/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

static int sti_reg_dir_dir(vm_t *vm, prog_t *prog)
{
    int reg = 0;
    short int sum[2] = {0};
    int to_add = 0;
    int to_cpy = 0;

    my_memcpy(&reg, &vm->mem[(prog->pc + 2) % MEM_SIZE], 1);
    if (!is_reg_exist(reg))
        return 84;
    my_memcpy(&sum[0], &vm->mem[(prog->pc + 3) % MEM_SIZE], IND_SIZE);
    my_memcpy(&sum[1], &vm->mem[(prog->pc + 5) % MEM_SIZE], IND_SIZE);
    sum[0] = convert_endian_number_short(sum[0]);
    sum[1] = convert_endian_number_short(sum[1]);
    to_add = sum[0] + sum[1];
    to_add = (to_add < 0) ? ((to_add % MEM_SIZE) + MEM_SIZE) : (to_add);
    to_cpy = convert_endian_number(prog->r[reg - 1]);
    my_memcpy(&vm->mem[(prog->pc + to_add % IDX_MOD) % MEM_SIZE], \
            &to_cpy, REG_SIZE);
    prog->pc = (prog->pc + 7) % MEM_SIZE;
    return 0;
}

static int sti_reg_dir_reg(vm_t *vm, prog_t *prog)
{
    int reg[2] = {0};
    short int sum[2] = {0};
    int to_add = 0;
    int to_cpy = 0;

    my_memcpy(&reg[0], &vm->mem[(prog->pc + 2) % MEM_SIZE], 1);
    my_memcpy(&reg[1], &vm->mem[(prog->pc + 5) % MEM_SIZE], 1);
    if (!is_reg_exist(reg[0]) || !is_reg_exist(reg[1]))
        return 84;
    my_memcpy(&sum[0], &vm->mem[(prog->pc + 3) % MEM_SIZE], IND_SIZE);
    sum[0] = convert_endian_number_short(sum[0]);
    my_memcpy(&sum[1], &prog->r[reg[1] - 1], IND_SIZE);
    to_add = sum[0] + sum[1];
    to_add = (to_add < 0) ? ((to_add % MEM_SIZE) + MEM_SIZE) : (to_add);
    to_cpy = convert_endian_number(prog->r[reg[0] - 1]);
    my_memcpy(&vm->mem[(prog->pc + to_add % IDX_MOD) % MEM_SIZE], \
            &to_cpy, REG_SIZE);
    prog->pc = (prog->pc + 6) % MEM_SIZE;
    return 0;
}

int sti_reg_dir_all(vm_t *vm, prog_t *prog, args_type_t arg[3])
{
    if (arg[2] == T_DIR)
        return sti_reg_dir_dir(vm, prog);
    if (arg[2] == T_REG)
        return sti_reg_dir_reg(vm, prog);
    return 84;
}
