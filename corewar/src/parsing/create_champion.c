/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

__attribute__((unused)) static bool is_cor_file_extension(char *str)
{
    str = my_revstr(str);
    if (my_strlen(str) < 4) {
        my_putstr(2, "Error: Filename too short\n");
        return false;
    }
    if (str[0] != 'r' || \
        str[1] != 'o' || \
        str[2] != 'c' || \
        str[3] != '.') {
        my_putstr(2, "Error: Is not a .cor file\n");
        return false;
    }
    str = my_revstr(str);
    return true;
}

int recup_champion(champion_t *champion, char **av, int i)
{
    if (!av[i]) {
        my_putstr(2, "No champion specified.\n");
        return -84;
    }
    if ((champion->fd = open(av[i], O_RDONLY)) == -1) {
        my_putstr(2, "Error in function open: No such file or directory.\n");
        return -84;
    }
    if (check_header(champion, av[i]) < 0)
        return -84;
    return ++i;
}

int create_champion(game_t *game, int id, char **av, int i)
{
    if (((i = recup_prog_number(game, id, av, i)) < 0) ||
            ((i = recup_load_address(game, id, av, i)) < 0) ||
            ((i = recup_champion(game->champions[id], av, i)) < 0))
        return -84;
    return i;
}
