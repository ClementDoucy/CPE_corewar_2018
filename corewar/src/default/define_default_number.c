/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "corewar.h"

int define_default_number(game_t *game)
{
    bool one = false;
    bool two = false;
    bool three = false;
    bool four = false;

    for (int i = 0; i < game->nb_champions; i++) {
        game->champions[i]->number == 1 ? one = true : one;
        game->champions[i]->number == 2 ? two = true : one;
        game->champions[i]->number == 3 ? three = true : one;
        game->champions[i]->number == 4 ? four = true : one;
    }
    if (one == false)
        return 1;
    if (two == false)
        return 2;
    if (three == false)
        return 3;
    if (four == false)
        return 4;
    return -84;
}
