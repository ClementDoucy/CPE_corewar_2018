/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "instructions.h"

static char *get_player_name_from_number(game_t *infos, const int nb)
{
    for (int i = 0; i < infos->nb_champions; i++)
        if (infos->champions[i]->number == nb)
            return infos->champions[i]->name;
    return NULL;
}

static void display_alive(const int player_number, const char *name)
{
    my_putstr(1, "The player ");
    my_put_nbr(player_number);
    my_putstr(1, "(");
    my_putstr(1, name);
    my_putstr(1, ") is alive.\n");
}

int live(vm_t *vm, prog_t *prog)
{
    int player_number = 0;
    char *name = NULL;

    my_memcpy(&player_number, &vm->mem[(prog->pc + 1) % MEM_SIZE], 4UL);
    player_number = convert_endian_number(player_number);
    name = get_player_name_from_number(vm->infos, player_number);
    prog->said_live = true;
    vm->cy.nbr_live -= 1;
    if (name) {
        display_alive(player_number, name);
        vm->cy.winner = player_number;
    }
    prog->pc = (prog->pc + 5) % MEM_SIZE;
    return 0;
}
