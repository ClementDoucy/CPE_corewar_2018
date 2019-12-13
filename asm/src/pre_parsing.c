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

err_type_t check_double_label(char *label, labelizer_t *label_tab, int nb_max)
{
    if (!label)
        return 0;
    for (int i = 0; i != nb_max; i++) {
        label = removed_del(label);
        if (my_strcmp(label, label_tab[i].label) == 0) {
            my_print(2, "Double Label : %s\n", label_tab[i].label);
            free(label);
            return DOUBLE_LABEL;
        }
    }
    free(label);
    return 0;
}

labelizer_t *init_struct_label(labelizer_t *label_tab, int nb_max)
{
    for (int i = 0; i != nb_max; i++) {
        label_tab[i].label = "null";
        label_tab[i].offset = 0;
    }
    return label_tab;
}

int count_nb_label(FILE *src)
{
    char *line = NULL;
    char **separating = NULL;
    int nb_label = 0;

    while ((line = read_file(src))) {
        if (char_in('.', line)) {
            free(line);
            continue;
        }
        separating = str_to_word_array(line, " ,");
        if (char_in(':', line) == true && char_in(':', separating[0]))
            nb_label++;
        if (line != NULL)
            free(line);
        destroy_2d_tab((void **)separating);
    }
    return (nb_label);
}

int fill_label_tab(pre_parse_t **cp_pre_parse, int *index)
{
    int ret = 0;
    pre_parse_t *pre_parse = *cp_pre_parse;

    if (pre_parse->label_tab == NULL || pre_parse->separating == NULL)
        return 84;
    if (char_in(':', pre_parse->separating[0]) == true) {
        if ((ret = check_double_label(my_strdup(pre_parse->separating[0]),
            pre_parse->label_tab, pre_parse->nb_label)) < 0)
            return ret;
        pre_parse->label_tab[*index].offset = pre_parse->offset + 1;
        pre_parse->label_tab[*index].label = my_strdup
            (pre_parse->separating[0]);
        pre_parse->label_tab[*index].label[my_strlen(pre_parse->label_tab
            [*index].label) - 1] = '\0';
        if ((ret = check_label_char(my_strdup(pre_parse->separating[0]),
            pre_parse->label_tab, pre_parse->nb_label)) < 0)
            return ret;
        (*index)++;
    }
    return 0;
}

labelizer_t *pre_parsing(FILE *src, int *prog_size)
{
    pre_parse_t *pre_parse = malloc(sizeof(pre_parse_t));
    labelizer_t *label_tab = NULL;

    if (pre_parse == NULL) return (NULL);
    pre_parse = init_pre_parse(pre_parse, count_nb_label(src));
    init_struct_label(pre_parse->label_tab, pre_parse->nb_label);
    fseek(src, 0, SEEK_SET);
    if ((pre_parse = step_read(pre_parse, src)) == NULL)
        return NULL;
    fseek(src, 0, SEEK_SET);
    label_tab = pre_parse->label_tab;
    *prog_size = pre_parse->offset;
    free(pre_parse);
    return label_tab;
}
