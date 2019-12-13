/*
** EPITECH PROJECT, 2019
** my_print.c
** File description:
** tools to print
*/

#include "my_print.h"

ssize_t my_print(int fd, const char *format, ...)
{
    ssize_t value = 0;
    size_t size = 0;
    char *str = NULL;
    va_list list;

    va_start(list, format);
    size = len_print(format, list);
    str = gen_str(format, list, size);
    va_end(list);
    value = write(fd, str, size - 1);
    free(str);
    return value;
}

size_t len_print(const char *format, va_list origin_list)
{
    va_list list;
    size_t size = 0;

    va_copy(list, origin_list);
    for (int i = 0; format[i] != '\0'; i++) {
        if (detect_flag(&format[i])) {
            size--;
            size += len_param(format[i + 1], list);
            i += 1;
        }
        size++;
    }
    va_end(list);
    return size + 1;
}

char *gen_str(const char *format, va_list list, size_t size)
{
    char *str = NULL;
    char *tmp = NULL;
    int i = 0;

    if (!(str = malloc(sizeof(char) * size)))
        return NULL;
    for (int k = 0; i < (int)size - 1; k++) {
        if (detect_flag(&format[k])) {
            str[i] = '\0';
            tmp = param_dup(format[k + 1], list);
            str = my_strcat_wmlc(str, tmp, i);
            i += my_strlen(tmp) - 1;
            free(tmp);
            k += 1;
        } else
            str[i] = format[k];
        i++;
    }
    return str;
}

char *param_dup(char flag, va_list list)
{
    char *str = NULL;

    if (flag == 's')
        str = my_strdup(va_arg(list, char *));
    else
        str = int_to_str(va_arg(list, int));
    return str;
}
