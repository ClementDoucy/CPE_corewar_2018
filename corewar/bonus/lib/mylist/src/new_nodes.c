/*
** EPITECH PROJECT, 2019
** particle
** File description:
** new_nodes
*/

#include "linked_list.h"

list_node_t *create_node(void *data)
{
    list_node_t *new_node = malloc(sizeof(list_node_t));

    if (new_node == NULL)
        return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int add_node(list_t *self, void *data)
{
    list_node_t *new_node = create_node(data);

    if (new_node == NULL)
        return 84;
    if (self->head != NULL)
        new_node->next = self->head;
    self->head = new_node;
    if (self->tail == NULL)
        self->tail = new_node;
    return 0;
}

int append_node(list_t *self, void *data)
{
    list_node_t *new_node = create_node(data);

    if (new_node == NULL)
        return 84;
    if (self->tail != NULL)
        self->tail->next = new_node;
    self->tail = new_node;
    if (self->head == NULL)
        self->head = new_node;
    return 0;
}

