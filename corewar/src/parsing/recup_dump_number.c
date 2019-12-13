/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"

int recup_dump_number(game_t *game, char **av)
{
    if (!my_strcmp(av[1], "-dump")) {
        if (!av[2]) {
            my_putstr(2, "-dump argument needs one argument\n");
            return -84;
        } else if (!is_str_int(av[2])) {
            my_putstr(2, "-dump argument ");
            my_putstr(2, av[2]);
            my_putstr(2, " is invalid. Please enter a positive number.\n");
            return -84;
        }
        if ((game->dump = my_atoi(av[2])) < 0) {
            my_putstr(2, "-dump argument ");
            my_putstr(2, av[2]);
            my_putstr(2, " is invalid. Please enter a positive number.\n");
            return -84;
        }
        return 3;
    }
    return 1;
}
