/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for bonus
*/

#include "my_print.h"
#include "asm.h"

int main(int ac, char **av)
{
    char **arr = str_2d_dup(av);

    if (print_asm_usage(ac, av))
        return 0;
    if (ac == 1)
        return launch(NULL);
    for (int i = 1; i < ac; i++) {
        i != 1 ? write(1, "\n", 1) : 0;
        my_print(1, "%s being assembled...\n", arr[i]);
        if (launch(av[i]))
            my_print(2, "Assembly failed with %s.\n", arr[i]);
        else
            my_print(1, "Assembly succeeded with %s.\n", arr[i]);
    }
    destroy_2d_tab((void **)arr);
    return 0;
}
