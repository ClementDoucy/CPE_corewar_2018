/*
** EPITECH PROJECT, 2019
** error_handling.c
** File description:
** error management
*/

#include "tools.h"
#include "asm.h"

bool is_label_defined(labelizer_t *labels, char *current)
{
    for (int i = 0; labels && labels[i].label; i++)
        if (are_eq_str(labels[i].label, current))
            return true;
    put_error("Undefined label.");
    return false;
}

void *malloc_failed(void)
{
    put_error("Malloc failed.");
    return NULL;
}

bool is_integer(const char *str)
{
    if (!str)
        return false;
    if (*str == '-')
        str++;
    for (; *str; str++)
        if (*str < '0' || *str > '9')
            return false;
    return true;
}

bool is_valid_type(param_type_t type, ins_id_t id, int i, char *arg)
{
    static const args_type_t type_check[5] = {
        T_REG,
        T_DIR,
        T_IND,
        T_DIR,
        T_IND
    };
    static bool (*const valid_arg[5])(char *) = {
        &is_valid_reg,
        &is_valid_dir,
        &is_valid_ind,
        &is_valid_dir_lab,
        &is_valid_ind_lab
    };

    if (type_check[type] != (op_tab[id].type[i] & type_check[type])) {
        put_error("Invalid argument type.");
        return false;
    }
    return valid_arg[type](arg);
}
