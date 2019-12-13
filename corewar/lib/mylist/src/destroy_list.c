/*
** EPITECH PROJECT, 2019
** particle
** File description:
** destroy_list
*/

#include "linked_list.h"

void destroy_list(list_t *self, void (*destroy_elem)(void *))
{
    list_node_t *tmp = NULL;

    if (!self)
        return;
    while (self->head != NULL) {
        tmp = self->head->next;
        if (destroy_elem != NULL)
            destroy_elem(self->head->data);
        free(self->head);
        self->head = tmp;
    }
    self->head = NULL;
    self->tail = NULL;
    free(self);
    self = NULL;
}
