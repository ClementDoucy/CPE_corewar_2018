/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** load_champions
*/

#include "corewar.h"
#include "mystring.h"
#include "instructions.h"

static int launch_vm(vm_t *vm)
{
    unsigned int cycle_to_die = CYCLE_TO_DIE;

    for (int i = 0; vm->head_champions != NULL; vm->cy.cycle++, i++) {
        if (i == vm->infos->dump)
            break;
        update_cycle(vm, &cycle_to_die);
        execute_processes(vm);
    }
    if (vm->infos->dump != -1)
        dump_mem(vm);
    if (vm->cy.winner != 0)
        display_winner(vm);
    return 0;
}

int start_corewar(game_t *game)
{
    vm_t *vm = init_corewar(game);
    int retval;

    if (!vm)
        return 84;
    retval = launch_vm(vm);
    destroy_vm(vm);
    return retval;
}
