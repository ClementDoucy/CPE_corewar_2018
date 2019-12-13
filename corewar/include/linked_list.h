/*
** EPITECH PROJECT, 2019
** particle
** File description:
** linked_list
*/

#ifndef LINKED_LIST_H_
    #define LINKED_LIST_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct list_node_s
{
    void *data;
    struct list_node_s *next;
} list_node_t;

typedef struct list_s
{
    struct list_node_s *head;
    struct list_node_s *tail;
} list_t;

list_t *new_list(void);
void init_list(list_t *list);
void destroy_list(list_t *self, void (*destroy_elem)(void *));

void pop_top_node(list_t *self);

list_node_t *create_node(void *data);

int add_node(list_t *self, void *data);
int append_node(list_t *self, void *data);

list_t *split_to_new_list(list_t *parent, int spliter);

char **list_to_arr(list_t *list);

#endif /* !LINKED_LIST_H_ */
