/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for asm
*/

#include "my_print.h"
#include "asm.h"
#include <stdio.h>

int main(int ac, char **av)
{
    if (print_asm_usage(ac, av))
        return 0;
    if (ac != 2) {
        my_print(2, "Error: %d arguments given but 1 is required.\n", ac - 1);
        return 84;
    }
    return launch(av[1]);
}
