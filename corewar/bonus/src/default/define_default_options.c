/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "corewar.h"

int define_default_options(game_t *game)
{
    for (int i = 0; i < game->nb_champions; i++) {
        if (game->champions[i]->number == -1)
            game->champions[i]->number = define_default_number(game);
    }
    return define_default_address(game);
}
