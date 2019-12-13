/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** update_cycle
*/

#include "corewar.h"

static void update_cycle_to_die(vm_t *vm, unsigned int *cycle_to_die)
{
    if (vm->cy.nbr_live <= 0 && *cycle_to_die > CYCLE_DELTA) {
        vm->cy.nbr_live = NBR_LIVE;
        *cycle_to_die -= CYCLE_DELTA;
    }
    if (vm->cy.cycle >= *cycle_to_die)
        vm->cy.cycle = 0;
}

static void remove_process(prog_t **head, prog_t **p, prog_t **prev)
{
    prog_t *tmp;

    if (*prev == NULL) {
        tmp = (*head);
        (*head) = (*head)->next;
        (*p) = (*head);
        (*prev) = NULL;
    } else {
        (*prev) = (*p);
        (*prev)->next = (*p)->next;
        tmp = (*p);
        (*p) = (*prev)->next;
    }
    free(tmp);
}

static void update_living_processes(vm_t *vm, unsigned int *cycle_to_die)
{
    prog_t *prev = NULL;
    bool val;

    if (vm->cy.cycle != *cycle_to_die)
        return;
    for (prog_t *p = vm->head_champions; p != NULL;) {
        val = p->said_live;
        p->said_live = false;
        if (val == false)
            remove_process(&(vm->head_champions), &p, &prev);
        else
            p = p->next;
        if (!p)
            return;
    }
}

void update_cycle(vm_t *vm, unsigned int *cycle_to_die)
{
    update_living_processes(vm, cycle_to_die);
    update_cycle_to_die(vm, cycle_to_die);
}