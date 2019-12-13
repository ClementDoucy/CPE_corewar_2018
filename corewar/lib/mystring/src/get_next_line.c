/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** get_next_line
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static char *reallocat__(char *line, int resize)
{
    char *new_line = malloc(resize);

    IS_MALLOCD(new_line);
    my_memset_(new_line, resize, 0);
    if (!line)
        return new_line;
    my_strcpy_(new_line, line);
    free(line);
    return new_line;
}

static int is_line_ended__(char *line, int my_read, char *mem)
{
    if (!line)
        return -1;
    for (int i = 0; i < my_read; i++)
        if (line[i] == '\n') {
            my_memset_(mem, READ_SIZE + 1, 0);
            my_strcpy_(mem, (&line[i + 1]));
            line[i] = 0;
            return i;
        }
    return -1;
}

static int concat_mem__(char *mem, char **line)
{
    int len = 0;

    if (mem[0] == 0)
        return 0;
    my_strlen_(mem, len);
    if (!((*line) = malloc(len + 1)))
        return -1;
    my_memset_((*line), len + 1, 0);
    my_strcpy_((*line), mem);
    my_memset_(mem, READ_SIZE + 1, 0);
    return len;
}

char *get_next_line(int fd)
{
    static char mem[READ_SIZE];
    char *line = NULL;
    int my_read;
    int m = 0;

    CHECK_FILE(fd, READ_SIZE);
    IS_CONCATED(my_read = concat_mem__(mem, &line));
    for (int i = 0; is_line_ended__(line, my_read, mem) == -1; i++) {
        IS_MALLOCD(line = reallocat__(line, my_read + READ_SIZE + 1));
        IS_READ_OK(m = read(fd, &line[my_read], READ_SIZE));
        my_read += m;
        if (my_read == 0) {
            free(line);
            return NULL;
        }
        BREAK_IF_EOF(m);
    }
    return line;
}