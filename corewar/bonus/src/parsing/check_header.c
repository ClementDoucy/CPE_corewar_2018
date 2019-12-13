/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** main
*/

#include "mystring.h"
#include "corewar.h"
#include "op.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static bool is_correct_magic_number(header_t *header)
{
    header->magic = convert_endian_number(header->magic);
    if (header->magic != COREWAR_EXEC_MAGIC) {
        my_putstr(2, "Wrong executable magic number.\n");
        return false;
    }
    return true;
}

static bool is_correct_prog_size(champion_t *champion, char *av)
{
    char *buf = NULL;

    if (champion->prog_size < 0) {
        my_putstr(2, av);
        my_putstr(2, " : Wrong program size in the header\n");
        return false;
    }
    if (!(buf = malloc(sizeof(char) * (champion->prog_size + 1)))) {
        my_putstr(2, "Error: malloc failed");
        return false;
    }
    if (read(champion->fd, buf, champion->prog_size) != champion->prog_size || \
            read(champion->fd, buf, 1) != 0) {
        free(buf);
        my_putstr(2, av);
        my_putstr(2, " : Wrong program size in the header\n");
        return false;
    }
    free(buf);
    return true;
}

int check_header(champion_t *champion, char *av)
{
    header_t *header = malloc(sizeof(header_t) + 1);

    if (!header)
        return -84;
    if (read(champion->fd, header, sizeof(header_t)) != sizeof(header_t)) {
        my_putstr(2, av);
        my_putstr(2, " is not an executable.\n");
        return -84;
    }
    champion->prog_size = convert_endian_number(header->prog_size);
    if ((!is_correct_magic_number(header)) || \
            (!(champion->name = my_strdup(header->prog_name))) || \
            (!is_correct_prog_size(champion, av)) || \
            (!(champion->comment = my_strdup(header->comment))))
        return -84;
    if (lseek(champion->fd, sizeof(header_t), SEEK_SET) != sizeof(header_t))
        return -84;
    free(header);
    return 0;
}
