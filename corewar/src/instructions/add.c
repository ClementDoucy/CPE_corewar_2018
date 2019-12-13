/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

int add(vm_t *vm, prog_t *prog)
{
    unsigned char coding_byte = vm->mem[(prog->pc + 1) % MEM_SIZE];
    int reg[3] = {0};

    if (coding_byte != 0x54) {
        modify_carry(prog, false);
        return 84;
    }
    for (int i = 0; i < 3; i++) {
        my_memcpy(&reg[i], &vm->mem[(prog->pc + (i + 2)) % MEM_SIZE], 1);
        if (!is_reg_exist(reg[i])) {
            modify_carry(prog, false);
            return 84;
        }
    }
    prog->r[reg[2] - 1] = prog->r[reg[0] - 1] + prog->r[reg[1] - 1];
    prog->pc = (prog->pc + 5) % MEM_SIZE;
    modify_carry(prog, true);
    return 0;
}
