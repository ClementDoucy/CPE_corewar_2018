/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** load_champions
*/

#include "corewar.h"
#include "mystring.h"
#include "instructions.h"
#include <unistd.h>

int nb_proc(vm_t *vm)
{
    int nb = 0;

    for (prog_t *p = vm->head_champions; p; p = p->next, nb++);
    return nb;
}

static void print_mem(vm_t *vm, int i, int to_die)
{
    system("clear");
    printf("Global clock: %d | cycle : [%d / %d]\n", i, vm->cy.cycle, to_die);
    printf("Number of processes: %d\n", nb_proc(vm));
    dump_mem(vm);
    usleep(10000);
}

static int launch_vm(vm_t *vm)
{
    unsigned int cycle_to_die = CYCLE_TO_DIE;

    for (int i = 0; vm->head_champions != NULL; vm->cy.cycle++, i++) {
        if (i == vm->infos->dump)
            break;
        if ((i % 100) == 0)
            print_mem(vm, i, cycle_to_die);
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
