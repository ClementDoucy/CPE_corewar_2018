/*
** EPITECH PROJECT, 2019
** get_param_value.c
** File description:
** get value of instruction arguments
*/

#include "tools.h"
#include "asm.h"

void *get_reg_value(char *args)
{
    char *reg = malloc(sizeof(char));
    void *value = NULL;

    if (!reg) {
        put_error("Malloc failed.");
        return NULL;
    }
    *reg = (char)my_getnbr(args + 1);
    value = reg;
    return value;
}

void *get_dir_value(char *args)
{
    int *dir = malloc(sizeof(int));
    void *value = NULL;

    if (!dir) {
        put_error("Malloc failed.");
        return NULL;
    }
    *dir = my_getnbr(args + 1);
    value = dir;
    return value;
}

void *get_ind_value(char *args)
{
    short *ind = malloc(sizeof(short));
    void *value = NULL;

    if (!ind) {
        put_error("Malloc failed.");
        return NULL;
    }
    *ind = (short)my_getnbr(args);
    value = ind;
    return value;
}

void *get_lab_value(char *args)
{
    char *lab = NULL;
    void *value = NULL;

    for (; *args && *args != ':'; args++);
    if (!*args) {
        put_error("Invalid label.");
        return NULL;
    }
    args++;
    if (!(lab = my_strdup(args))) {
        put_error("Malloc failed.");
        return NULL;
    }
    value = lab;
    return value;
}

void *get_param_value(char *args, param_type_t type, ins_id_t id)
{
    void *value = NULL;

    if (type == IND_LAB)
        type--;
    if (type == DIR && op_tab[id].my_dir_size == 2)
        type++;
    value = value_fun[type](args);
    return value;
}
