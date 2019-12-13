/*
** EPITECH PROJECT, 2019
** get_instruction.c
** File description:
** get instruction in ins node
*/

#include <unistd.h>
#include "tools.h"
#include "asm.h"

static param_type_t get_param_type(char *arg)
{
    if (char_in('%', arg))
        return (char_in(':', arg) ? DIR_LAB : DIR);
    if (char_in(':', arg))
        return IND_LAB;
    return (char_in('r', arg) ? REG : IND);
}

static ins_id_t get_ins_id(char *line, int i)
{
    ins_id_t id = UNKNOW;

    line[i] = '\0';
    for (int k = 0; k < SIZE_INS; k++)
        if (are_eq_str(line, op_tab[k].mnemonique)) {
            id = k;
            break;
        }
    line[i] = ' ';
    return id;
}

static bool get_ins_param(
    ins_args_t *args, char **arr, ins_id_t id, labelizer_t *labels)
{
    for (int i = 0; arr[i]; i++) {
        args[i].type = get_param_type(arr[i]);
        if (!is_valid_type(args[i].type, id, i, arr[i]))
            return false;
        if (!(args[i].value = get_param_value(arr[i], args[i].type, id)))
            return malloc_failed();
        if ((args[i].type == DIR_LAB || args[i].type == IND_LAB)
            && !is_label_defined(labels, (char *)args[i].value))
            return false;
    }
    return true;
}

static ins_args_t *get_ins_args(char *line, ins_id_t id, labelizer_t *labels)
{
    ins_args_t *args = malloc(sizeof(ins_args_t) * op_tab[id].nbr_args);
    char **arr = str_to_word_array(line, " ,");
    char *tmp = NULL;

    if (!args || !arr)
        return malloc_failed();
    for (int i = 0; arr[i]; i++) {
        if (!(tmp = str_clean(arr[i]))) {
            destroy_2d_tab((void **)arr);
            return malloc_failed();
        }
        free(arr[i]);
        arr[i] = tmp;
    }
    if (!(get_ins_param(args, arr, id, labels))) {
        destroy_2d_tab((void **)arr);
        return NULL;
    }
    destroy_2d_tab((void **)arr);
    return args;
}

bool get_instruction(ins_node_t *node, char *line, labelizer_t *labels)
{
    int i = 0;

    for (; line[i] && line[i] != ' '; i++);
    if (!line[i]) {
        put_error("Invalid instruction.");
        return false;
    } if ((node->id = get_ins_id(line, i)) == UNKNOW) {
        put_error("Invalid instruction.");
        return false;
    } if (!(node->args = get_ins_args(&line[i + 1], node->id, labels)))
        return false;
    return true;
}
