/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** destroy_vm
*/

#include <unistd.h>
#include "corewar.h"

static void free_progs(prog_t *head)
{
    prog_t *tmp;

    for (prog_t *p = head; p != NULL;) {
        tmp = p->next;
        free(p);
        if (tmp == NULL)
            break;
        p = tmp;
    }
}

void destroy_vm(vm_t *vm)
{
    free_progs(vm->head_champions);
    for (int i = 0; i < vm->infos->nb_champions; i++) {
        free(vm->infos->champions[i]->name);
        free(vm->infos->champions[i]->comment);
        close(vm->infos->champions[i]->fd);
    }
    free_game(vm->infos);
    free(vm->mem);
    free(vm);
}