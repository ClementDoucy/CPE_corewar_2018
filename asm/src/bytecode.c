/*
** EPITECH PROJECT, 2019
** bytecode.c
** File description:
** functions to write bytecode
*/

#include <unistd.h>
#include "asm.h"

static bool write_string_as_bc(int bin, char *str, size_t size)
{
    for (size_t i = 0; i < size; i++)
        if (write(bin, &(str[i]), sizeof(char)) == -1)
            return false;
    for (int i = 0; i < 4; i++)
        if (write(bin, "\0", sizeof(char)) == -1)
            return false;
    return true;
}

static bool write_header(int bin, header_t header)
{
    header.magic = convert_endian_number(header.magic);
    if (write(bin, &(header.magic), sizeof(int)) == -1)
        return false;
    if (!write_string_as_bc(bin, header.prog_name, PROG_NAME_LENGTH))
        return false;
    header.prog_size = convert_endian_number(header.prog_size);
    if (write(bin, &(header.prog_size), sizeof(int)) == -1)
        return false;
    if (!write_string_as_bc(bin, header.comment, COMMENT_LENGTH))
        return false;
    return true;
}

static bool write_coding_byte(int bin, ins_node_t *node, size_t *current_os)
{
    char tmp = 0;
    char byte = 0;
    size_t size = (size_t)op_tab[node->id].nbr_args;

    if (!op_tab[node->id].description)
        return true;
    for (size_t i = 0; i < size; i++) {
        byte <<= (i ? 2 : 0);
        tmp = (char)node->args[i].type + 1;
        tmp -= (tmp == 4 || tmp == 5 ? 2 : 0);
        byte += tmp;
    }
    size = MAX_ARGS_NUMBER - size;
    for (size_t k = 0; k < size; k++)
        byte <<= 2;
    if (write(bin, &byte, sizeof(char)) == -1)
        return false;
    *current_os += sizeof(char);
    return true;
}

static bool write_instruction(
    int bin, ins_node_t *node, size_t *offset, labelizer_t *labels)
{
    if (!node->next)
        return true;
    offset[0] = offset[1];
    if (write(bin, &(op_tab[node->id].code), sizeof(char)) == -1)
        return false;
    offset[1] += sizeof(char);
    if (!write_coding_byte(bin, node, &(offset[1])))
        return false;
    if (!write_arguments(bin, node, offset, labels))
        return false;
    return write_instruction(bin, node->next, offset, labels);
}

bool write_bytecode(int bin, parser_t *parser)
{
    size_t offset[2] = {0, 0};

    if (!write_header(bin, parser->header))
        return false;
    if (!write_instruction(bin, parser->head, offset, parser->labels))
        return false;
    return true;
}
