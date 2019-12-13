/*
** EPITECH PROJECT, 2019
** particle
** File description:
** remove_nodes
*/

#include "linked_list.h"

void pop_top_node(list_t *self)
{
    list_node_t *tmp = NULL;

    if (self->head != NULL) {
        tmp = self->head->next;
        free(self->head);
        self->head = tmp;
    }
}
