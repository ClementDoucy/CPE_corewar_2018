/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"

game_t *create_game(void)
{
    game_t *game = malloc(sizeof(game_t));

    if (!game)
        return NULL;
    if (!(game->champions = malloc(sizeof(champion_t *) * 5)))
        return NULL;
    for (int i = 0; i < 4; i++) {
        if (!(game->champions[i] = malloc(sizeof(champion_t))))
            return NULL;
    }
    game->champions[4] = NULL;
    game->dump = -1;
    game->nb_champions = 0;
    return game;
}

void free_game(game_t *game)
{
    if (!game)
        return;
    for (int i = 0; i < 5; i++)
        free(game->champions[i]);
    free(game->champions);
    free(game);
}

game_t *recup_options(int ac, char **av)
{
    game_t *game = create_game();
    int i = 0;

    if (!game)
        return NULL;
    if ((i = recup_dump_number(game, av)) < 0)
        return NULL;
    while (i < ac) {
        if (game->nb_champions == 4) {
            my_putstr(2, "The number of champion load is above the limit.\n");
            return NULL;
        }
        i = create_champion(game, game->nb_champions, av, i);
        if (i < 0)
            return NULL;
        game->nb_champions++;
    }
    return game;
}
