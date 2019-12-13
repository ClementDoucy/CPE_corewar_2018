/*
** EPITECH PROJECT, 2019
** error_handling_tests.c
** File description:
** tests for error handling
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "tools.h"
#include "asm.h"

void redirect_all_std(void);

Test(Test_1, is_label_defined_1)
{
    labelizer_t labels[4] = {
        {"toto", 0},
        {"titi", 0},
        {"tata", 0},
        {NULL, 0}
    };
    char *current = "tata";

    cr_assert_eq(is_label_defined(labels, current), true);
}

Test(Test_2, is_label_defined_2, .init = redirect_all_std)
{
    labelizer_t labels[4] = {
        {"toto", 0},
        {"titi", 0},
        {"tata", 0},
        {NULL, 0}
    };
    char *current = "tutu";

    cr_assert_eq(is_label_defined(labels, current), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Undefined label.\n");
}

Test(Test_3, malloc_failed, .init = redirect_all_std)
{
    cr_assert_null(malloc_failed());
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Malloc failed.\n");
}

Test(Test_4, is_integer_1)
{
    cr_assert_eq(is_integer(NULL), false);
}

Test(Test_5, is_integer_2)
{
    cr_assert_eq(is_integer("d1a25a"), false);
}

Test(Test_6, is_integer_3)
{
    cr_assert_eq(is_integer("-129d87"), false);
}

Test(Test_7, is_integer_4)
{
    cr_assert_eq(is_integer("-1297"), true);
}

Test(Test_8, is_integer_5)
{
    cr_assert_eq(is_integer("83173"), true);
}

Test(Test_9, is_valid_type_1, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_type(DIR, ST, 1, "%-400"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid argument type.\n");
}

Test(Test_10, is_valid_type_2, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_type(IND, ST, 1, "400"), true);
}

Test(Test_11, put_warning_1, .init = redirect_all_std)
{
    char *expected = "[1m[35mWarning:[0m[0m "
        "Warning must me printed in magenta.\n";

    put_warning("Warning must me printed in magenta.");
    cr_assert_stderr_eq_str(expected);
}

Test(Test_12, is_valid_reg_1, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_reg("r8"), true);
}

Test(Test_13, is_valid_reg_2, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_reg("8r"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid register argument.\n");
}

Test(Test_14, is_valid_reg_3, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_reg("r64"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid register argument.\n");
}

Test(Test_15, is_valid_reg_4, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_reg("rhello"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid register argument.\n");
}

Test(Test_16, is_valid_reg_5, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_reg(NULL), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid register argument.\n");
}

Test(Test_17, is_valid_dir_1, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_dir("%42"), true);
    cr_assert_eq(is_valid_dir("%-42"), true);
    cr_assert_eq(is_valid_dir("%0"), true);
}

Test(Test_18, is_valid_dir_2, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_dir(NULL), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid direct argument.\n");
}

Test(Test_19, is_valid_dir_3, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_dir("631%3616"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid direct argument.\n");
}

Test(Test_20, is_valid_dir_4, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_dir("%6561a5155"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid direct argument.\n");
}

Test(Test_21, is_valid_ind_1, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_ind("3618317"), true);
    cr_assert_eq(is_valid_ind("-501591"), true);
    cr_assert_eq(is_valid_ind("0"), true);
}

Test(Test_22, is_valid_ind_2, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_ind(NULL), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid indirect argument.\n");
}

Test(Test_23, is_valid_ind_3, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_ind("361831:7"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid indirect argument.\n");
}

Test(Test_24, is_valid_dir_lab_1, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_dir_lab("%:hello"), true);
}

Test(Test_25, is_valid_dir_lab_2, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_dir_lab("*:hello"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid direct label call.\n");
}

Test(Test_26, is_valid_dir_lab_3, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_dir_lab("%/hello"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid direct label call.\n");
}

Test(Test_27, is_valid_dir_lab_4, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_dir_lab(NULL), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid direct label call.\n");
}

Test(Test_28, is_valid_ind_lab_1, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_ind_lab(":hello"), true);
}

Test(Test_29, is_valid_ind_lab_2, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_ind_lab(NULL), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid indirect label call.\n");
}

Test(Test_30, is_valid_ind_lab_3, .init = redirect_all_std)
{
    cr_assert_eq(is_valid_ind_lab("%hello"), false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid indirect label call.\n");
}
