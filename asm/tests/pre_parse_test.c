/*
** EPITECH PROJECT, 2019
** parsing_tests.c
** File description:
** test for parsing
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "tools.h"
#include "asm.h"

void redirect_all_std(void);

Test(Test_1, check_double_label)
{
    char *label = my_strdup("l2");
    labelizer_t *label_tab = malloc(sizeof(labelizer_t));
    int nb_max = 1;

    label_tab->label = my_strdup("l2");
    cr_assert_eq(check_double_label(label, label_tab, nb_max), DOUBLE_LABEL);
}

Test(Test_2, check_double_label)
{
    char *label = my_strdup("l2");
    labelizer_t *label_tab = malloc(sizeof(labelizer_t));
    int nb_max = 1;

    label_tab->label = my_strdup("l1");
    cr_assert_eq(check_double_label(label, label_tab, nb_max), 0);
}

Test(Test_3, init_struct_label_error)
{
    labelizer_t label_tab[2] = {{"l2", 0}, {"live", 0}};
    int nb_max = 2;

    cr_assert_neq(init_struct_label(label_tab, nb_max), NULL);
}

Test(Test_4, fill_label_tab_error_null)
{
    pre_parse_t *pre_parse = malloc(sizeof(pre_parse_t));
    int index = 0;

    pre_parse->label_tab = NULL;
    pre_parse->line = NULL;
    pre_parse->separating = NULL;
    cr_assert_eq(fill_label_tab(&pre_parse, &index), 84);
}

Test(Test_5, fill_label_tab_no_error)
{
    pre_parse_t *pre_parse = malloc(sizeof(pre_parse_t));
    int index = 0;

    pre_parse->label_tab = malloc(sizeof(labelizer_t));
    pre_parse->label_tab->label = "Bonjour";
    pre_parse->line = "hello";
    pre_parse->separating = str_to_word_array("hello hees h", " ");
    cr_assert_eq(fill_label_tab(&pre_parse, &index), 0);
}

Test(Test_6, fill_label_tab_error_invalid_label)
{
    pre_parse_t *pre_parse = malloc(sizeof(pre_parse_t));
    int index = 0;

    pre_parse->label_tab = malloc(sizeof(labelizer_t));
    pre_parse->label_tab->label = "Bonjour:";
    pre_parse->line = "Bonjour:";
    pre_parse->nb_label = 1;
    pre_parse->separating = str_to_word_array(
        "Bonjour: Bonjour Bonjour", " ");
    cr_assert_eq(fill_label_tab(&pre_parse, &index), INVALID_LABEL);
}

Test(Test_7, fill_label_tab_error_double_label)
{
    pre_parse_t *pre_parse = malloc(sizeof(pre_parse_t));
    int index = 0;

    pre_parse->label_tab = malloc(sizeof(labelizer_t));
    pre_parse->label_tab->label = "bonjour";
    pre_parse->line = "bonjour";
    pre_parse->nb_label = 1;
    pre_parse->separating = str_to_word_array(
        "bonjour: bonjour bonjour", " ");
    cr_assert_eq(fill_label_tab(&pre_parse, &index), DOUBLE_LABEL);
}

Test(Test_8, pre_parse_no_initialise)
{
    pre_parse_t *pre_parse = malloc(sizeof(pre_parse_t));
    labelizer_t *label_tab = NULL;

    cr_assert_neq(init_pre_parse(pre_parse, 1), NULL);
}

Test(Test_9, removed_del)
{
    cr_assert_neq(removed_del(my_strdup("hello:")), NULL);
}

Test(Test_10, check_label_char)
{
    pre_parse_t *pre_parse = malloc(sizeof(pre_parse_t));

    pre_parse->label_tab = malloc(sizeof(labelizer_t));
    pre_parse->label_tab->label = my_strdup("Bonjour:");
    pre_parse->line = my_strdup("Bonjour:");
    pre_parse->nb_label = 1;
    pre_parse->separating = str_to_word_array(
        "Bonjour: Bonjour Bonjour", " ");
    cr_assert_eq(check_label_char(
        pre_parse->line, pre_parse->label_tab, 1), INVALID_LABEL);
}

Test(Test_11, check_label_char)
{
    pre_parse_t *pre_parse = malloc(sizeof(pre_parse_t));

    pre_parse->label_tab = malloc(sizeof(labelizer_t));
    pre_parse->label_tab->label = my_strdup("bonjour");
    pre_parse->line = my_strdup("bonjour");
    pre_parse->nb_label = 1;
    pre_parse->separating = str_to_word_array(
        "bonjour bonjour bonjour", " ");
    cr_assert_eq(
        check_label_char(pre_parse->line, pre_parse->label_tab, 1), 0);
}

Test(Test_12, count_nb_arg)
{
    char **line = str_to_word_array("live: %1 #coucou", " ,");

    cr_assert_eq(count_arg(line), 1);
}

Test(Test_13, count_nb_arg_no_arg)
{
    char **line = str_to_word_array(" ", ",");

    cr_assert_eq(count_arg(line), 0);
}

Test(Test_14, count_nb_arg_nothing)
{
    char **line = str_to_word_array("", " ,");

    cr_assert_eq(count_arg(line), 84);
}

Test(Test_15, count_multi_arg)
{
    char **line = str_to_word_array("sti r10,%-510,%0", " ,");

    cr_assert_eq(count_arg(line), 3);
}

Test(Test_16, check_error)
{
    char **line = str_to_word_array("live %1, %2", " ,");

    cr_assert_eq(check_error(line, op_tab[0]), ARG_NB);
}

Test(Test_17, check_error)
{
    char **line = str_to_word_array("live %1", " ,");

    cr_assert_eq(check_error(line, op_tab[0]), 5);
}

Test(Test_18, check_error)
{
    char **line = str_to_word_array("ld %0, r11", " ,");

    cr_assert_eq(check_error(line, op_tab[1]), 7);
}

Test(Test_19, check_error)
{
    char **line = str_to_word_array("st r5,r2", " ,");

    cr_assert_eq(check_error(line, op_tab[2]), 4);
}

Test(Test_20, check_error)
{
    char **line = str_to_word_array("add r2,r4,r2", " ,");

    cr_assert_eq(check_error(line, op_tab[3]), 5);
}

Test(Test_21, check_error)
{
    char **line = str_to_word_array("sub r2,r4,r2", " ,");

    cr_assert_eq(check_error(line, op_tab[4]), 5);
}

Test(Test_22, check_error)
{
    char **line = str_to_word_array("and r6,%2147483648,r8", " ,");

    cr_assert_eq(check_error(line, op_tab[5]), 8);
}

Test(Test_23, check_error)
{
    char **line = str_to_word_array("or r2,r2,r2", " ,");

    cr_assert_eq(check_error(line, op_tab[6]), 5);
}

Test(Test_24, check_error)
{
    char **line = str_to_word_array("xor r10,r10,r10", " ,");

    cr_assert_eq(check_error(line, op_tab[7]), 5);
}

Test(Test_25, check_error)
{
    char **line = str_to_word_array("zjmp %192", " ,");

    cr_assert_eq(check_error(line, op_tab[8]), 3);
}

Test(Test_26, check_error)
{
    char **line = str_to_word_array("ldi %3,%5,r2", " ,");

    cr_assert_eq(check_error(line, op_tab[9]), 7);
}

Test(Test_27, check_error)
{
    char **line = str_to_word_array("sti r1,%5,%1", " ,");

    cr_assert_eq(check_error(line, op_tab[10]), 7);
}

Test(Test_28, check_error)
{
    char **line = str_to_word_array("fork %3", " ,");

    cr_assert_eq(check_error(line, op_tab[11]), 3);
}

Test(Test_29, check_error)
{
    char **line = str_to_word_array("lld 2,r4", " ,");

    cr_assert_eq(check_error(line, op_tab[12]), 5);
}

Test(Test_30, check_error)
{
    char **line = str_to_word_array("lldi 2,r4,r1", " ,");

    cr_assert_eq(check_error(line, op_tab[13]), 6);
}

Test(Test_31, check_error)
{
    char **line = str_to_word_array("lfork %2", " ,");

    cr_assert_eq(check_error(line, op_tab[14]), 3);
}

Test(Test_32, check_error)
{
    char **line = str_to_word_array("aff r2", " ,");

    cr_assert_eq(check_error(line, op_tab[15]), 3);
}
