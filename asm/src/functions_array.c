/*
** EPITECH PROJECT, 2019
** functions_array.c
** File description:
** contains functions pointer array
*/

#include "asm.h"

const line_fn_ptr_t line_types[4] =
{
    {&is_comment, COM},
    {&is_empty_line, EMPTY},
    {&is_header_name, H_NAME},
    {&is_header_comment, H_COM}
};

void *(*const value_fun[4])(char *) =
{
    &get_reg_value,
    &get_dir_value,
    &get_ind_value,
    &get_lab_value
};

bool (*const write_value[3])(int, void *, size_t *) =
{
    &write_register,
    &write_direct,
    &write_indirect
};

bool (*const write_label[2])(int, void *, size_t *, labelizer_t *) =
{
    &write_direct_label,
    &write_indirect_label
};

bool (*const fn_ptr[3])(const char *, header_t *, h_error_t *) =
{
    &handle_header_name,
    &handle_header_comment,
    NULL
};
