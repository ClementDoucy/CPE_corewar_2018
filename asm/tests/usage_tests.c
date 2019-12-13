/*
** EPITECH PROJECT, 2019
** usage_tests.c
** File description:
** unit test for usage
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "asm.h"

void redirect_all_std(void);

Test(Test_1, print_usage_asm_1, .init = redirect_all_std)
{
    int ac = 2;
    char *av[3] = {"./asm", "-h", NULL};
    char *expected = "USAGE\n\t./asm file_name[.s]\n\n"
        "DESCRIPTION\n\tfile_name\tfile in assembly language to be "
        "converted into file_name.cor, an\n\t\t\t"
        "executable in the Virtual Machine.\n";

    cr_assert_eq(print_asm_usage(ac, av), true);
    cr_assert_stdout_eq_str(expected);
}

Test(Test_2, print_usage_asm_2, .init = redirect_all_std)
{
    int ac = 2;
    char *av[3] = {"banane", "-h", NULL};
    char *expected = "USAGE\n\tbanane file_name[.s]\n\n"
        "DESCRIPTION\n\tfile_name\tfile in assembly language to be "
        "converted into file_name.cor, an\n\t\t\t"
        "executable in the Virtual Machine.\n";

    cr_assert_eq(print_asm_usage(ac, av), true);
    cr_assert_stdout_eq_str(expected);
}

Test(Test_3, print_usage_asm_3, .init = redirect_all_std)
{
    int ac = 2;
    char *av[3] = {"./asm", "zork.s", NULL};

    cr_assert_eq(print_asm_usage(ac, av), false);
}
