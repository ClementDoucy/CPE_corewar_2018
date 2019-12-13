/*
** EPITECH PROJECT, 2018
** matching nodes
** File description:
** matching nodes
*/

#include "my_print.h"
#include "asm.h"

int count_arg(char **line)
{
    int count = 0;

    if (line == NULL)
        return (84);
    for (int i = 1; line[i] != NULL; i++) {
        if (my_strcmp(line[i], "#") == 0 || char_in('#', line[i]))
            break;
        count++;
    }
    return count;
}

err_type_t check_error(char **line, op_t op)
{
    int nb_arg = count_arg(line);
    int offset = 0;

    if (nb_arg != op.nbr_args)
        return ARG_NB;
    for (int i = 1; i != nb_arg + 1; i++) {
        if (my_strcmp(line[i], "") == 0)
            continue;
        if (char_in('%', line[i]))
            offset += op.my_dir_size;
        else if (line[i][0] == 'r')
            offset += 1;
        else
            offset += 2;
    }
    if (op.description == true)
        offset++;
    return ++offset;
}

err_type_t match_or_not(pre_parse_t *pre_parse, int (*cmp)
    (char const *, char const *))
{
    int i = 0;
    int const len_tab = 16;
    int tmp_offset = 0;
    int j = 0;

    if (pre_parse->separating == NULL) return EMPTY_LINE;
    for (; pre_parse->separating[j] != NULL &&
        char_in(':', pre_parse->separating[j]) == true; j++);
    if (pre_parse->separating[j] == NULL) return NO_INSTRUCTION;
    while (i != len_tab) {
        if ((*cmp)(op_tab[i].mnemonique, pre_parse->separating[j]) == 0) {
            if ((tmp_offset = check_error
                (&pre_parse->separating[j], op_tab[i])) < 0)
                return tmp_offset;
            return tmp_offset + pre_parse->offset;
        }
        tmp_offset = 0;
        i++;
    }
    return UNKNOW_INSTRUCTION;
}
