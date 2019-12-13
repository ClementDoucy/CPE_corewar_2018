/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"

static int error_invalid_argument(char *av)
{
    my_putstr(2, "-n argument ");
    my_putstr(2, av);
    my_putstr(2, " is invalid.\nEnter a number between 1 and 4.\n");
    return -84;
}

int recup_prog_number(game_t *game, int id, char **av, int i)
{
    if (!my_strcmp(av[i], "-n")) {
        if (!av[++i]) {
            my_putstr(2, "-n argument needs one argument\n");
            return -84;
        } else if (!is_str_int(av[i]))
            return error_invalid_argument(av[i]);
        if ((game->champions[id]->number = my_atoi(av[i])) < 1 || \
                game->champions[id]->number > 4)
            return error_invalid_argument(av[i]);
        return ++i;
    } else
        game->champions[id]->number = -1;
    return i;
}
