/*
** EPITECH PROJECT, 2019
** instruction_parsing.c
** File description:
** parse instruction
*/

#include "asm.h"

static void *parsing_error(ins_node_t *head, char *line)
{
    if (line)
        free(line);
    destroy_ins_list(head, NULL);
    return NULL;
}

static void *header_in_ins(ins_node_t *head, char *line, line_type_t current)
{
    if (current == H_NAME)
        put_error("Header name must be defined at begin of file.");
    if (current == H_COM)
        put_error("Header comment must be defined at begin of file.");
    return parsing_error(head, line);
}

static bool is_real_ins(ins_node_t **node, char *line, labelizer_t *labels)
{
    int nb_space = 0;
    int i = 0;

    for (; line[i]; i++)
        if (line[i] == ' ')
            nb_space++;
    if (!nb_space)
        return true;
    for (i = 0; line[i] && line[i] != ':'; i++);
    i = (!line[i] || line[i - 1] == '%' || line[i - 1] == ' ' ? 0 : i + 1);
    i = (i && line[i] == ' ' ? i + 1 : i);
    if (!(get_instruction(*node, &line[i], labels)))
        return false;
    if (!((*node)->next = init_ins_node()))
        return false;
    *node = (*node)->next;
    return true;
}

void *parse_instruction(FILE *src, labelizer_t *labels)
{
    ins_node_t *node = init_ins_node();
    void *head = node;
    char *line = NULL;
    line_type_t current = 0;

    if (!node)
        return NULL;
    while ((line = read_file(src))) {
        current = get_line_type(line);
        if (current == H_NAME || current == H_COM)
            return header_in_ins(head, line, current);
        if (current == INS && !(is_real_ins(&node, line, labels)))
            return parsing_error(head, line);
        free(line);
    }
    return head;
}
