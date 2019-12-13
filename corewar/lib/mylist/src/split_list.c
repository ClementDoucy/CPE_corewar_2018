/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** split_list
*/

#include "linked_list.h"

static void new_top_node_tail(list_t *giver, list_t *granted)
{
    list_node_t *new = giver->head;
    list_node_t *tmp = granted->tail;

    if (new == NULL)
        return;
    if (giver->tail == giver->head)
        giver->tail = NULL;
    giver->head = giver->head->next;
    granted->tail = new;
    new->next = NULL;
    if (granted->head == NULL)
        granted->head = new;
    if (tmp != NULL)
        tmp->next = granted->tail;
}

list_t *split_to_new_list(list_t *parent, int spliter)
{
    list_t *new = new_list();

    if (new == NULL)
        return NULL;
    for (int i = 0; i < spliter; i++)
        new_top_node_tail(parent, new);
    return new;
}
