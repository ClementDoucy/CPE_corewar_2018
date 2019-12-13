/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** arr
*/

#include "mystring.h"

char **arr_remove_index(char **arr, int ind)
{
    int size = my_arrlen(arr);
    char **new_arr = NULL;
    int j = 0;

    if (!(new_arr = malloc(sizeof(char *) * size)))
        return NULL;
    new_arr[size - 1] = NULL;
    for (int i = 0; arr[i]; i++, j++) {
        if (i == ind)
            j--;
        else
            new_arr[j] = arr[i];
    }
    free(arr[ind]);
    free(arr);
    return new_arr;
}

char **arr_add_index(char **arr, char *stradd, int ind)
{
    int size = my_arrlen(arr) + 1;
    char **new_arr = NULL;
    int i = 0;

    if (stradd == NULL)
        return NULL;
    if (!(new_arr = malloc(sizeof(char *) * (size + 1))))
        return NULL;
    new_arr[size] = NULL;
    (ind == -1) ? (ind = size - 1) : (ind);
    for (int j = 0; i < size; i++, j++) {
        if (i == ind) {
            new_arr[i++] = stradd;
            ind = 0;
        }
        new_arr[i] = arr[j];
    }
    free(arr);
    return new_arr;
}

char **my_arrdup(char **arr)
{
    int size = my_arrlen(arr);
    char **new_arr = NULL;

    if (!(new_arr = malloc(sizeof(char *) * (size + 1))))
        return NULL;
    new_arr[size] = NULL;
    for (int i = 0; i < size; i++)
        new_arr[i] = my_strdup(arr[i]);
    return new_arr;
}