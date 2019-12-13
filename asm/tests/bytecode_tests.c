/*
** EPITECH PROJECT, 2019
** bytecode_tests.c
** File description:
** unit tests for bytecode part
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tools.h"
#include "asm.h"

void redirect_all_std(void);

Test(Test_1, write_register_1, .init = redirect_all_std)
{
    char c = 3;
    char expected[2] = {3, '\0'};
    size_t current_os = 0;

    cr_assert_eq(write_register(1, (void *)&c, &current_os), true);
    cr_assert_stdout_eq_str(expected);
    cr_assert_eq(current_os, 1);
}

Test(Test_2, write_register_2)
{
    char c = 3;
    size_t current_os = 0;

    cr_assert_eq(write_register(-1, (void *)&c, &current_os), false);
    cr_assert_eq(current_os, 0);
}

Test(Test_3, write_direct_1)
{
    int a = 3;
    size_t current_os = 0;
    int bin = open("data", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int check = 0;

    cr_assert_eq(write_direct(bin, (void *)&a, &current_os), true);
    close(bin);
    bin = open("data", O_RDONLY, 0666);
    read(bin, &check, 4);
    cr_assert_eq(check, a);
    cr_assert_eq(current_os, 4);
    close(bin);
}

Test(Test_4, write_direct_2)
{
    int a = 3;
    size_t current_os = 0;

    cr_assert_eq(write_direct(-1, (void *)&a, &current_os), false);
    cr_assert_eq(current_os, 0);
}

Test(Test_5, write_indirect_1)
{
    short a = 3;
    size_t current_os = 0;
    int bin = open("data", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    short check = 0;

    cr_assert_eq(write_indirect(bin, (void *)&a, &current_os), true);
    close(bin);
    bin = open("data", O_RDONLY, 0666);
    read(bin, &check, 2);
    cr_assert_eq(check, a);
    cr_assert_eq(current_os, 2);
    close(bin);
}

Test(Test_6, write_indirect_2)
{
    short a = 3;
    size_t current_os = 0;

    cr_assert_eq(write_indirect(-1, (void *)&a, &current_os), false);
    cr_assert_eq(current_os, 0);
}

Test(Test_7, write_direct_label_1)
{
    size_t offset[2] = {0, 0};
    char *label = "l2";
    labelizer_t labels[2] = {{"l2", 10}, {NULL, 0}};
    int bin = open("data", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int check = 0;

    cr_assert_eq(
        write_direct_label(bin, (void *)label, offset, labels), true);
    cr_assert_eq(offset[1], 4);
    close(bin);
    bin = open("data", O_RDONLY, 0666);
    read(bin, &check, 4);
    close(bin);
    cr_assert_eq(check, convert_endian_number(9));
}

Test(Test_8, write_direct_label_2)
{
    size_t offset[2] = {0, 0};
    char *label = "l2";
    labelizer_t labels[2] = {{"l2", 10}, {NULL, 0}};

    cr_assert_eq(
        write_direct_label(-1, (void *)label, offset, labels), false);
}

Test(Test_9, write_indirect_label_1)
{
    size_t offset[2] = {0, 0};
    char *label = "l2";
    labelizer_t labels[2] = {{"l2", 10}, {NULL, 0}};
    short bin = open("data", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    short check = 0;

    cr_assert_eq(
        write_indirect_label(bin, (void *)label, offset, labels), true);
    cr_assert_eq(offset[1], 2);
    close(bin);
    bin = open("data", O_RDONLY, 0666);
    read(bin, &check, 2);
    close(bin);
    cr_assert_eq(check, convert_endian_number_short(9));
}

Test(Test_10, write_indirect_label_2)
{
    size_t offset[2] = {0, 0};
    char *label = "l2";
    labelizer_t labels[2] = {{"l2", 10}, {NULL, 0}};

    cr_assert_eq(
        write_indirect_label(-1, (void *)label, offset, labels), false);
}

Test(Test_11, zork_test)
{
    FILE *my_zork = NULL;
    FILE *ref_zork = NULL;

    cr_assert_eq(launch(my_strdup("./champions/zork.s")), 0);
    my_zork = fopen("./zork.cor", "r");
    cr_assert_not_null(my_zork);
    ref_zork = fopen("./champions/ref_zork.cor", "r");
    cr_assert_not_null(ref_zork);
    cr_assert_file_contents_eq(my_zork, ref_zork);
    fclose(my_zork);
    fclose(ref_zork);
    system("rm ./zork.cor");
}
