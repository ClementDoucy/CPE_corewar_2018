/*
** EPITECH PROJECT, 2019
** asm.h
** File description:
** header file for asm
*/

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "op.h"
#include "enum.h"
#include "struct.h"

#define SIZE_INS 16

extern const line_fn_ptr_t line_types[4];
extern void *(*const value_fun[4])(char *);
extern bool (*const write_value[3])(int, void *, size_t *);
extern bool (*const write_label[2])(int, void *, size_t *, labelizer_t *);
extern bool (*const fn_ptr[3])(const char *, header_t *, h_error_t *);

int launch(char *);
int create_bin_file(char *);
bool is_empty_line(const char *);
bool is_header_name(const char *);
bool is_header_comment(const char *);
bool is_comment(const char *);
int run_asm(FILE *, int *);
parser_t *parse_file(FILE *);
int put_error(const char *);
void put_warning(const char *);
line_type_t get_line_type(const char *);
parser_t *init_parser(void);
bool handle_header_name(const char *, header_t *, h_error_t *);
bool handle_header_comment(const char *, header_t *, h_error_t *);
bool check_h_name_err(const char *, h_error_t *);
bool check_h_com_err(const char *, h_error_t *);
ins_node_t *init_ins_node(void);
void destroy_ins_list(ins_node_t *, ins_node_t *);
char *read_file(FILE *);
void *parse_instruction(FILE *, labelizer_t *);
bool get_instruction(ins_node_t *, char *, labelizer_t *);
void *get_param_value(char *, param_type_t, ins_id_t);
void *get_reg_value(char *);
void *get_dir_value(char *);
void *get_ind_value(char *);
void *get_lab_value(char *);
labelizer_t *pre_parsing(FILE *src, int *prog_size);
err_type_t match_or_not(pre_parse_t *pre_parse, int (*cmp)
    (char const *, char const *));
void display_separing(char **separing);
pre_parse_t *init_pre_parse(pre_parse_t *pre_parse, int nb_label);
void my_free_useless(pre_parse_t **cp_pre_parse);
bool is_label_defined(labelizer_t *, char *);
bool write_bytecode(int, parser_t *);
int convert_endian_number(int);
pre_parse_t *step_read(pre_parse_t *pre_parse, FILE *src);
int fill_label_tab(pre_parse_t **pre_parse, int *index);
void *malloc_failed(void);
bool write_arguments(int, ins_node_t *, size_t *, labelizer_t *);
bool write_register(int, void *, size_t *);
bool write_direct(int, void *, size_t *);
bool write_indirect(int, void *, size_t *);
bool write_direct_label(int, void *, size_t *, labelizer_t *);
bool write_indirect_label(int, void *, size_t *, labelizer_t *);
short int convert_endian_number_short(short int);
bool print_asm_usage(int, char **);
char *removed_del(char *label);
bool is_valid_type(param_type_t, ins_id_t, int, char *);
err_type_t check_label_char(char *label, labelizer_t *label_tab, int nb_max);
bool is_valid_reg(char *);
bool is_valid_dir(char *);
bool is_valid_ind(char *);
bool is_valid_dir_lab(char *);
bool is_valid_ind_lab(char *);
bool is_integer(const char *);
err_type_t check_double_label(
    char *label, labelizer_t *label_tab, int nb_max);
labelizer_t *init_struct_label(labelizer_t *label_tab, int nb_max);
int count_nb_label(FILE *src);
int count_arg(char **line);
err_type_t check_error(char **line, op_t op);
