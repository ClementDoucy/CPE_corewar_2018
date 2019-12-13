/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"

int usage(const char *filename)
{
    my_putstr(1, "USAGE:\n\t");
    my_putstr(1, filename);
    my_putstr(1, " [-dump nbr_cycle] [[-n prog_number] [-a load_address] ");
    my_putstr(1, "prog_name] ...\n\nDESCRIPTION\n");
    my_putstr(1, "\t-dump nbr_cycle\tdumps the memory after the nbr_cycle ");
    my_putstr(1, "execution (if the round isn't\n");
    my_putstr(1, "\t\t\talready over) with the following format:  ");
    my_putstr(1, "32 bytes/line in\n");
    my_putstr(1, "\t\t\thexadecimal (AOBCDEFE1DD3...)\n");
    my_putstr(1, "\t-n prog_number\tsets the next program's number.  ");
    my_putstr(1, "By default, the first free number\n");
    my_putstr(1, "\t\t\tin the parameter order\n");
    my_putstr(1, "\t-a load_address\tsets the next program's");
    my_putstr(1, "loading address.  ");
    my_putstr(1, "When no address is\n");
    my_putstr(1, "\t\t\tspecified, optimize the addresses so that ");
    my_putstr(1, "the processes are as far\n");
    my_putstr(1, "\t\t\taway from each other as possible. ");
    my_putstr(1, " The addresses are MEM_SIZE modulo\n");
    return 0;
}
