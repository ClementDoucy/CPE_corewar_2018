/*
** EPITECH PROJECT, 2019
** tools.h
** File description:
** header file for tools
*/

#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

char *my_strdup(char *);
size_t my_strlen(const char *);
char *my_strcat(char *, char *);
void my_puts(char *);
char *my_strcat(char *, char *);
void my_put_2d_str(char **);
int my_getnbr(char *);
void destroy_2d_tab(void **);
void my_putstr(char *);
void my_putstr_stderr(const char *);
void print_2d_str(char **);
void my_puts_stderr(char *);
char **realloc_2d_str(char **, size_t);
size_t str_2d_len(char **);
char **str_2d_dup(char **);
bool are_eq_str(char *, char *);
int my_strncmp(const char *, const char *, size_t);
int my_strcmp(const char *, const char *);
int is_same_str(const char *, const char *);
int is_same_str_stop(const char *, const char *, char);
char *str_clean(char *);
char *my_strcpy(char *, const char *);
char *my_strncpy(char *, const char *, size_t);
char *my_strndup(const char *, size_t);
int char_in(char, char const *);
char **str_to_word_array(char *strin, char *delims);
void **free_arr_null(void **arr, bool free_arr);
void *sfree_null(void *ptr);
void remove_comment(char *);

#endif
