/*
** EPITECH PROJECT, 2019
** particle
** File description:
** linked_list
*/

#include "linked_list.h"

void init_list(list_t *list)
{
    list->head = NULL;
    list->tail = NULL;
}

list_t *new_list(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (list == NULL)
        return NULL;
    init_list(list);
    return list;
}