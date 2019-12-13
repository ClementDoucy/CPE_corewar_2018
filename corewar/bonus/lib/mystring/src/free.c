/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** free
*/

#include "mystring.h"

void *sfree_null(void *ptr)
{
    if (ptr)
        free(ptr);
    return NULL;
}

void sfree(void *ptr)
{
    if (ptr)
        free(ptr);
}

int ifree(void *ptr)
{
    if (ptr) {
        free (ptr);
        return 1;
    }
    return 0;
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