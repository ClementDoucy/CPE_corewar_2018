/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"

int main(int ac, char **av)
{
    game_t *game = NULL;

    if (ac < 2)
        return error_no_argument(av[0]);
    if (!my_strcmp(av[1], "-h"))
        return usage(av[0]);
    if (!(game = recup_options(ac, av)) || check_options_correct(game))
        return 84;
    if (define_default_options(game) == 84)
        return 84;
    if (start_corewar(game) == 84)
        return 84;
    return 0;
}
