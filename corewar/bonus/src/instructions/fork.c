/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

static prog_t *copy_process(prog_t *new, prog_t *old)
{
    new->carry = old->carry;
    for (int i = 0; i < REG_NUMBER; i++)
        new->r[i] = old->r[i];
    new->next = NULL;
    return new;
}

static prog_t *create_new_process(prog_t *to_add, int index)
{
    prog_t *prog = new_champion(to_add->infos);

    if (!prog)
        return NULL;
    prog = copy_process(prog, to_add);
    prog->infos->address = (to_add->pc + index % IDX_MOD) % MEM_SIZE;
    prog->pc = (to_add->pc + index % IDX_MOD) % MEM_SIZE;
    return prog;
}

static prog_t *add_process(prog_t *list, prog_t *to_add, int index)
{
    prog_t *new = create_new_process(to_add, index);
    prog_t *tmp = list;

    if (!new)
        return NULL;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return list;
}

int my_fork(vm_t *vm, prog_t *prog)
{
    unsigned short int index = 0;

    my_memcpy(&index, &vm->mem[(prog->pc + 1) % MEM_SIZE], IND_SIZE);
    index = convert_endian_number_short(index);
    vm->head_champions = add_process(vm->head_champions, prog, index);
    prog->pc = (prog->pc + 3) % MEM_SIZE;
    return 0;
}
