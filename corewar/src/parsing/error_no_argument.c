/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"

int error_no_argument(char *filename)
{
    my_putstr(2, "USAGE:\n\t");
    my_putstr(2, filename);
    my_putstr(2, " [-dump nbr_cycle] [[-n prog_number] [-a load_adress] ");
    my_putstr(2, "prog_name] ...\n");
    my_putstr(2, "\nPress -h to know more about ...\n");
    return 84;
}
