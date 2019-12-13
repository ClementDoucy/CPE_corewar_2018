/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

int zjmp(vm_t *vm, prog_t *prog)
{
    short int index = 0;

    if (prog->carry == false) {
        prog->pc = (prog->pc + 3) % MEM_SIZE;
        return 0;
    }
    my_memcpy(&index, &vm->mem[(prog->pc + 1) % MEM_SIZE], IND_SIZE);
    index = convert_endian_number_short(index);
    prog->pc = (prog->pc + index % IDX_MOD) % MEM_SIZE;
    return 0;
}
