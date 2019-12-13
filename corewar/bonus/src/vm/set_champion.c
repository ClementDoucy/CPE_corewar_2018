/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** set_champion
*/

#include "corewar.h"
#include "mystring.h"

prog_t *new_champion(champion_t *desc)
{
    prog_t *new = malloc(sizeof(prog_t));

    if (!new) {
        my_putstr(2, "new_champion: alloc failed.\n");
        return NULL;
    }
    new->infos = desc;
    new->pc = desc->address;
    new->carry = 0;
    new->clock = 0;
    new->instruction = 0;
    for (uint i = 0; i < REG_NUMBER; i++)
        new->r[i] = 0;
    new->r[0] = desc->number;
    new->said_live = true;
    return new;
}

prog_t *init_champions(game_t *game)
{
    prog_t *p;
    prog_t *head = NULL;
    prog_t *tail = NULL;

    for (int i = 0; i < game->nb_champions; i++) {
        p = new_champion(game->champions[i]);
        if (p == NULL)
            return NULL;
        p->next = NULL;
        if (head == NULL)
            head = p;
        if (tail != NULL)
            tail->next = p;
        tail = p;
    }
    return head;
}

int set_champions_in_mem(vm_t *vm)
{
    for (int i = 0; i < vm->infos->nb_champions; i++) {
        if (load_program(vm, vm->infos->champions[i]) == 84) {
            my_putstr(2, "champions loading in memory failed, aborting.\n");
            return 84;
        }
    }
    return 0;
}
