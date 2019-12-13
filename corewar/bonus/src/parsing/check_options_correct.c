/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"

static int check_have_same_value_prog_number(game_t *game, int i)
{
    for (int j = i + 1; j < game->nb_champions; j++)
        if (game->champions[i]->number == game->champions[j]->number) {
            my_putstr(2, "double definition of prog_number.\n");
            return -84;
        }
    return 0;
}

static int check_have_same_value_load_address(game_t *game, int i)
{
    for (int j = i + 1; j < game->nb_champions; j++)
        if (game->champions[i]->address == game->champions[j]->address) {
            my_putstr(2, "double definition of load address.\n");
            return -84;
        }
    return 0;
}

int check_options_correct(game_t *game)
{
    for (int i = 0; i < game->nb_champions; i++) {
        if (game->champions[i]->number > 0 && \
                check_have_same_value_prog_number(game, i) < 0)
            return -84;
        else if (game->champions[i]->address > 0 && \
                check_have_same_value_load_address(game, i) < 0)
            return -84;
    }
    return 0;
}
