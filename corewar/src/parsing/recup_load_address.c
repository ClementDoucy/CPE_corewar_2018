/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "op.h"

static int error_load_address_no_argument(void)
{
    my_putstr(2, "-a argument needs one argument\n");
    return -84;
}

static int error_not_an_int(char *av)
{
    my_putstr(2, "-a argument ");
    my_putstr(2, av);
    my_putstr(2, " is invalid.\nEnter a positive number.\n");
    return -84;
}

static int address_in_hexa(game_t *game, int id, char **av, int i)
{
    if (my_strlen(av[i]) < 3)
        return error_not_an_int(av[i]);
    for (int j = 2; av[i][j]; j++)
        if (!char_in(av[i][j], "0123456789abcdefABCDEF"))
            return error_not_an_int(av[i]);
    game->champions[id]->address = my_hexa_to_dec(av[i]);
    game->champions[id]->address %= MEM_SIZE;
    if (game->champions[id]->address < 0)
        return -84;
    return ++i;
}

int recup_load_address(game_t *game, int id, char **av, int i)
{
    if (!my_strcmp(av[i], "-a")) {
        if (!av[++i])
            return error_load_address_no_argument();
        if (my_strncmp(av[i], "0x", 2) == 0)
            return address_in_hexa(game, id, av, i);
        if ((!is_str_int(av[i]) || \
            (game->champions[id]->address = my_atoi(av[i]) % MEM_SIZE) < 0))
            return error_not_an_int(av[i]);
        return ++i;
    } else
        game->champions[id]->address = -1;
    return i;
}
