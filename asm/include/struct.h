/*
** EPITECH PROJECT, 2019
** struct.h
** File description:
** header file for structure
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "op.h"
#include "enum.h"

typedef struct line_fn_ptr line_fn_ptr_t;
typedef struct header_error h_error_t;
typedef struct parser parser_t;
typedef struct labelizer labelizer_t;
typedef struct ins_node ins_node_t;
typedef struct ins_args ins_args_t;
typedef struct pre_parse pre_parse_t;

struct line_fn_ptr {
    bool (*fn)(const char *);
    line_type_t type;
};

struct header_error {
    bool name_catch;
    bool comment_catch;
    bool prev_was_name;
};

struct ins_args {
    param_type_t type;
    void *value;
};

struct ins_node {
    ins_id_t id;
    ins_args_t *args;
    ins_node_t *next;
};

struct labelizer {
    char *label;
    size_t offset;
};

struct parser {
    labelizer_t *labels;
    header_t header;
    h_error_t h_error;
    ins_node_t *head;
};

struct pre_parse {
    char *line;
    char **separating;
    size_t offset;
    int err_code;
    int nb_label;
    labelizer_t *label_tab;
};