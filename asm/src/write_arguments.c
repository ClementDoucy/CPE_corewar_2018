/*
** EPITECH PROJECT, 2019
** write_arguments.c
** File description:
** write instructions arguments in bytecode
*/

#include "asm.h"

static bool write_parameter(
    int bin, ins_args_t arg, size_t *offset, labelizer_t *labels)
{
    if (arg.type <= IND)
        return write_value[arg.type](bin, arg.value, &(offset[1]));
    else {
        arg.type -= 3;
        return write_label[arg.type](bin, arg.value, offset, labels);
    }
    return true;
}

bool write_arguments(
    int bin, ins_node_t *node, size_t *offset, labelizer_t *labels)
{
    bool except = op_tab[node->id].my_dir_size == 2;
    bool is_dir = false;
    size_t size = (size_t)op_tab[node->id].nbr_args;

    for (size_t i = 0; i < size; i++) {
        is_dir = (node->args[i].type == DIR || node->args[i].type == DIR_LAB);
        node->args[i].type += (except && is_dir ? 1 : 0);
        if (!write_parameter(bin, node->args[i], offset, labels))
            return false;
    }
    return true;
}
