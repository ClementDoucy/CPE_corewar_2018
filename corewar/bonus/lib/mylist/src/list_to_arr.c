/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** list_to_arr
*/

#include "linked_list.h"

static size_t len_list(list_t *list)
{
    list_node_t *p;
    size_t len = 0;

    if (list == NULL || list->head == NULL)
        return 0;
    p = list->head;
    while (p != NULL) {
        len++;
        p = p->next;
    }
    return len;
}

char **list_to_arr(list_t *list)
{
    size_t len = len_list(list);
    char **arr;
    int i = 0;

    if (len == 0)
        return NULL;
    arr = malloc(sizeof(char *) * (len + 1));
    if (arr == NULL)
        return NULL;
    arr[len] = NULL;
    for (list_node_t *p = list->head; p != NULL; p = p->next, i++)
        arr[i] = (char *) p->data;
    return arr;
}