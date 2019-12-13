/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** dump_mem
*/

#include <unistd.h>
#include "corewar.h"
#include "mystring.h"

static const char *HEX = "0123456789ABCDEF";

static int my_nblen(int nb)
{
    int len = 0;

    do {
        nb /= 16;
        len++;
    } while (nb > 0);
    return len;
}

static void dump_line_nb(int line, int j, int lock)
{
    int nb = line * lock;
    int len = my_nblen(nb) % 6;
    char head_line[7];

    if (j != 0)
        return;
    for (int i = 0; i < 7; i++)
        head_line[i] = ' ';
    for (int i = len; i > 0; i--) {
        head_line[i - 1] = HEX[nb % 16];
        nb /= 16;
    }
    head_line[5] = ':';
    write(1, head_line, 7);
}

static void my_putchar_hex(int c, bool pc)
{
    char nb[2];

    if (c < 0)
        c &= 0xFF;
    nb[0] = HEX[c / 16];
    nb[1] = HEX[c % 16];
    if (pc == true)
        my_putstr(1, "\e[33;1m");
    else if (nb[0] != '0' || nb[1] != '0')
        my_putstr(1, "\e[7;49;91m");
    write(1, nb, 2);
    my_putstr(1, "\e[0m");
}

static bool is_pc(vm_t *vm, int i, int j, int lock)
{
    int pos = i * lock + j;

    for (prog_t *p = vm->head_champions; p; p = p->next) {
        if (p->pc == pos)
            return true;
    }
    return false;
}

void dump_mem(vm_t *vm)
{
    static int lock = 32;
    int threshold = MEM_SIZE / lock;
    bool pc;

    for (int i = 0; i < threshold; i++) {
        for (int j = 0; j < lock; j++) {
            dump_line_nb(i, j, lock);
            pc = is_pc(vm, i, j, lock);
            my_putchar_hex(vm->mem[i * lock + j], pc);
            write(1, (j != (lock - 1)) ? (" ") : ("\n"), 1);
        }
    }
}
