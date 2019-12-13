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

Test(Test_1, get_line_type)
{
    char *line = "#hello";

    cr_assert_eq(get_line_type(line), COM);
}

Test(Test_2, get_line_type)
{
    char *line = "";

    cr_assert_eq(get_line_type(line), EMPTY);
}

Test(Test_3, get_line_type)
{
    char *line = ".name";

    cr_assert_eq(get_line_type(line), H_NAME);
}

Test(Test_4, get_line_type)
{
    char *line = ".comment";

    cr_assert_eq(get_line_type(line), H_COM);
}

Test(Test_5, get_line_type)
{
    char *line = "live %1";

    cr_assert_eq(get_line_type(line), INS);
}
