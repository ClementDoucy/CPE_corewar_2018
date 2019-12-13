/*
** EPITECH PROJECT, 2019
** launcher.c
** File description:
** pre_parsing for asm
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include "my_print.h"
#include "asm.h"

void my_free_useless(pre_parse_t **cp_pre_parse)
{
    pre_parse_t *pre_parse = *cp_pre_parse;

    if (pre_parse->separating != NULL) {
        for (int j = 0; pre_parse->separating[j] != NULL; j++)
            free(pre_parse->separating[j]);
        free(pre_parse->separating);
        pre_parse->separating = NULL;
    }
    if (pre_parse->line != NULL)
        free(pre_parse->line);
}

pre_parse_t *step_read(pre_parse_t *pre_parse, FILE *src)
{
    int index = 0;

    while ((pre_parse->line = read_file(src))) {
        if (char_in('.', pre_parse->line)) {
            free(pre_parse->line);
            continue;
        }
        pre_parse->separating = str_to_word_array(pre_parse->line, " ,");
        if (pre_parse->separating != NULL) {
            if (my_strcmp(pre_parse->separating[0], "#") == 0) continue;
        }
        pre_parse->err_code = fill_label_tab(&pre_parse, &index);
    if (pre_parse->err_code <= ARG_NB && pre_parse->err_code >= INVALID_LABEL)
            return NULL;
    if ((pre_parse->err_code = match_or_not(pre_parse, my_strcmp)) > 0)
            pre_parse->offset = pre_parse->err_code;
    if (pre_parse->err_code <= ARG_NB && pre_parse->err_code >= INVALID_LABEL)
            return NULL;
        my_free_useless(&pre_parse);
    } return pre_parse;
}

pre_parse_t *init_pre_parse(pre_parse_t *pre_parse, int nb_label)
{
    pre_parse->err_code = 0;
    pre_parse->label_tab = malloc(sizeof(labelizer_t) * (nb_label + 1));
    if (pre_parse->label_tab == NULL)
        return (NULL);
    pre_parse->label_tab[nb_label].label = NULL;
    pre_parse->line = NULL;
    pre_parse->offset = 0;
    pre_parse->nb_label = nb_label;
    pre_parse->separating = NULL;
    return pre_parse;
}

char *removed_del(char *label)
{
    for (int j = 0; label[j] != '\0'; j++) {
        if (label[j] == ':')
            label[j] = '\0';
    }
    return (label);
}

err_type_t check_label_char(char *label, labelizer_t *label_tab, int nb_max)
{
    if (!label)
        return 0;
    for (int i = 0; i != nb_max; i++) {
        label = removed_del(label);
        for (int j = 0; label_tab[i].label[j] != '\0'; j++) {
            if (char_in(label_tab[i].label[j], LABEL_CHARS) == false) {
                free(label);
                return INVALID_LABEL;
            }
        }
    }
    free(label);
    return 0;
}
