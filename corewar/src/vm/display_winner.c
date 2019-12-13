/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** display_winner
*/

#include "corewar.h"
#include "mystring.h"

void display_winner(vm_t *vm)
{
    char winner = vm->cy.winner + '0';

    my_putstr(1, "The player ");
    write(1, &(winner), 1);
    my_putstr(1, "(");
    my_putstr(1, vm->infos->champions[vm->cy.winner - 1]->name);
    my_putstr(1, ") has won.\n");
}
