/*
** EPITECH PROJECT, 2019
** mystring
** File description:
** str_to_word_array
*/

#include "tools.h"

size_t my_strcountw(char *str, char *delims)
{
    size_t words = 0;

    for (size_t i = 0; str[i];) {
        for (;str[i] && char_in(str[i], delims) == true; i++);
        if (str[i])
            words++;
        for (; str[i] && char_in(str[i], delims) == false; i++);
    }
    return words;
}

static size_t strlen_to_arg(char *str, char *delims)
{
    size_t len = 0;

    for (; str[len] && !char_in(str[len], delims); len++);
    return len;
}

static char **str_to_array(char *str, char **arr, size_t w,
                            char *delims)
{
    size_t len = 0;
    size_t index = 0;

    arr[w] = NULL;
    for (size_t i = 0; i < w; i++) {
        for (; str[index] && char_in(str[index], delims); index++);
        len = strlen_to_arg(&(str[index]), delims);
        arr[i] = malloc(sizeof(char) * (len + 1));
        if (!(arr[i]))
            return ((char **) free_arr_null((void **) arr, true));
        my_strncpy(arr[i], &(str[index]), len);
        index += len + 1;
    }
    return arr;
}

char **str_to_word_array(char *strin, char *delims)
{
    size_t words = my_strcountw(strin, delims);
    char **wordarray = (char **) malloc(sizeof(char *) * (words + 1));

    if (!words)
        return ((char **) sfree_null(wordarray));
    wordarray = str_to_array(strin, wordarray, words, delims);
    return wordarray;
}