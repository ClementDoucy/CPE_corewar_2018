/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

int aff(vm_t *vm, prog_t *prog)
{
    unsigned char coding_byte = vm->mem[(prog->pc + 1) % MEM_SIZE];
    int reg = 0;

    if (coding_byte != 0x40)
        return 84;
    my_memcpy(&reg, &vm->mem[(prog->pc + 2) % MEM_SIZE], 1);
    if (is_reg_exist(reg) == false)
        return 84;
    if (prog->r[reg - 1] == 42)
        my_putchar(1, '*');
    else
        my_putchar(1, prog->r[reg - 1] % 256);
    prog->pc = (prog->pc + 3) % MEM_SIZE;
    return 0;
}
