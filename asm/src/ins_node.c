/*
** EPITECH PROJECT, 2019
** ins_node.c
** File description:
** ins_node functions
*/

#include "asm.h"

ins_node_t *init_ins_node(void)
{
    ins_node_t *new = malloc(sizeof(ins_node_t));

    if (!new) {
        put_error("Malloc failed.");
        return NULL;
    }
    new->id = 0;
    new->args = NULL;
    new->next = NULL;
    return new;
}

void destroy_ins_list(ins_node_t *current, ins_node_t *previous)
{
    if (previous) {
        for (int i = 0; previous->args &&
            i < (int)op_tab[previous->id].nbr_args; i++)
            free(previous->args[i].value);
        previous->args ? free(previous->args) : 0;
        free(previous);
    }
    if (current)
        return destroy_ins_list(current->next, current);
}
