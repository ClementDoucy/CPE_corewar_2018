/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** init_corewar
*/

#include "corewar.h"
#include "mystring.h"

static vm_t *get_vm(game_t *game)
{
    char *mem = malloc(MEM_SIZE);
    vm_t *vm = malloc(sizeof(vm_t));

    if (!mem || !vm) {
        my_putstr(2, "get_vm: alloc failed.\n");
        return NULL;
    }
    vm->mem = my_memset(mem, 0, MEM_SIZE);
    vm->cy.nbr_live = NBR_LIVE;
    vm->cy.cycle = 0;
    vm->cy.winner = 0;
    vm->cy.p_alive = game->nb_champions;
    vm->infos = game;
    vm->head_champions = init_champions(game);
    if (!vm->head_champions)
        return NULL;
    return vm;
}

vm_t *init_corewar(game_t *game)
{
    vm_t *vm = get_vm(game);

    if (!vm)
        return NULL;
    if (vm->head_champions == NULL)
        return NULL;
    if (set_champions_in_mem(vm) == 84)
        return NULL;
    return vm;
}