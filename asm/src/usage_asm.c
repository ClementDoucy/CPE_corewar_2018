/*
** EPITECH PROJECT, 2019
** usage_asm.c
** File description:
** print usage
*/

#include "my_print.h"

bool print_asm_usage(int ac, char **av)
{
    static const char *usage = "file_name[.s]\n\n"
        "DESCRIPTION\n\tfile_name\tfile in assembly language to be "
        "converted into file_name.cor, an\n\t\t\t"
        "executable in the Virtual Machine.\n";

    if (ac != 2 || !are_eq_str(av[1], "-h"))
        return false;
    my_print(1, "USAGE\n\t%s %s", av[0], usage);
    return true;
}
