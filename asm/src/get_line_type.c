/*
** EPITECH PROJECT, 2019
** get_line_type.c
** File description:
** get line type
*/

#include "enum.h"
#include "struct.h"
#include "tools.h"
#include "asm.h"

bool is_comment(const char *line)
{
    return (line && *line == '#' ? true : false);
}

bool is_empty_line(const char *line)
{
    return (!line || *line == '\0' ? true : false);
}

bool is_header_name(const char *line)
{
    return (line && !my_strncmp(line, ".name", 5) ? true : false);
}

bool is_header_comment(const char *line)
{
    return (line && !my_strncmp(line, ".comment", 8) ? true : false);
}

line_type_t get_line_type(const char *line)
{
    for (int i = 0; i < 4; i++)
        if (line_types[i].fn(line))
            return line_types[i].type;
    return INS;
}
