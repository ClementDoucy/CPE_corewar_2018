/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** str_to_word_array
*/

#include "tools.h"

void *sfree_null(void *ptr)
{
    if (ptr)
        free(ptr);
    return NULL;
}

void **free_arr_null(void **arr, bool free_arr)
{
    if (!arr)
        return NULL;
    for (size_t i = 0; arr[i]; i++)
        free(arr[i]);
    if (free_arr == true)
        free(arr);
    return NULL;
}