/*
** EPITECH PROJECT, 2019
** my_print.h
** File description:
** header file for my_print
*/

#ifndef MY_PRINT_H_
#define MY_PRINT_H_

#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include "tools.h"

ssize_t my_print(int, const char *, ...);
size_t len_print(const char *, va_list);
bool detect_flag(const char *);
size_t len_param(char, va_list);
size_t len_int(int);
char *gen_str(const char *, va_list, size_t);
char *param_dup(char, va_list);
char *int_to_str(int);
int compute_div(int);
char *fill_str(int, size_t, int, char *);
char *my_strcat_wmlc(char *, char *, int);

#endif
