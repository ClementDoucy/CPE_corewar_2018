/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "op.h"

uint get_mem_used(game_t *game)
{
    uint mem_used = 0;

    for (int i = 0; i < game->nb_champions; i++)
        mem_used += game->champions[i]->prog_size;
    return mem_used;
}

int get_number_of_splitting_bytes(game_t *game, uint *split_size)
{
    uint mem_used = get_mem_used(game);

    if (mem_used > MEM_SIZE) {
        my_putstr(2, "The program sizes sum is greater than MEM_SIZE.\n");
        return 84;
    }
    *split_size = (MEM_SIZE - mem_used) / game->nb_champions;
    return 0;
}

int are_champions_overlapping(game_t *game, int i)
{
    int interv[2];
    int address = game->champions[i]->address;

    if (i == 0 || address == -1)
        return 0;
    interv[0] = game->champions[i - 1]->address;
    interv[1] = game->champions[i - 1]->prog_size +
                game->champions[i - 1]->address - 1;
    if (address >= interv[0] && address <= interv[1]) {
        my_putstr(2, "Overlap detected.\n");
        return 1;
    }
    return 0;
}

int define_default_address(game_t *game)
{
    uint split_size;
    int cursor = 0;

    if (get_number_of_splitting_bytes(game, &split_size) == 84)
        return 84;
    for (int i = 0; i < game->nb_champions; i++) {
        if (game->champions[i]->address == -1)
            game->champions[i]->address = cursor;
        else
            cursor = game->champions[i]->address;
        if (are_champions_overlapping(game, i))
            return 84;
        cursor += game->champions[i]->prog_size + split_size;
        cursor %= MEM_SIZE;
    }
    return 0;
}
