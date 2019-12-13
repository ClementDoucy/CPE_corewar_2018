/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** load_program
*/

#include <unistd.h>
#include "corewar.h"
#include "mystring.h"

int fill_mem(unsigned char *mem, int off, int fd, int size)
{
    char buf[size];

    if (read(fd, buf, size) != size) {
        my_putstr(2, "fill_mem: read failure.\n");
        return 84;
    }
    if (lseek(fd, sizeof(header_t), SEEK_SET) != sizeof(header_t)) {
        my_putstr(2, "fill_mem: lseek failure.\n");
        return 84;
    }
    for (int i = 0; i < size; i++)
        mem[off + i] = buf[i];
    return 0;
}

int load_program(vm_t *vm, champion_t *champ)
{
    int load_address = champ->address;
    int fd = champ->fd;
    int size = champ->prog_size;

    return fill_mem(vm->mem, load_address, fd, size);
}
