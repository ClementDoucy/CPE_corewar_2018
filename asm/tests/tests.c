/*
** EPITECH PROJECT, 2019
** tests.c
** File description:
** unit tests for asm
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "tools.h"
#include "asm.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(test_1, open_src_file, .init = redirect_all_std)
{
    char *filepath = "dzakndkza";

    cr_assert_eq(launch(filepath), 84);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m invalid file path.\n");
}

Test(test_2, create_bin_file_1)
{
    char *filepath = strdup("toto.s");
    int fd = 0;
    FILE *check = NULL;

    fd = create_bin_file(filepath);
    check = fopen("toto.cor", "r");
    cr_assert_not_null(check);
    if (check)
        fclose(check);
    if (fd != -1)
        close(fd);
    system("rm -rf toto.cor");
}

Test(test_3, create_bin_file_2)
{
    char *filepath = strdup("toto");
    int fd = 0;
    FILE *check = NULL;

    fd = create_bin_file(filepath);
    check = fopen("toto.cor", "r");
    cr_assert_not_null(check);
    if (check)
        fclose(check);
    if (fd != -1)
        close(fd);
    system("rm -rf toto.cor");
}

Test(test_4, create_bin_file_3)
{
    char *filepath = strdup("toto.tata");
    int fd = 0;
    FILE *check = NULL;

    fd = create_bin_file(filepath);
    check = fopen("toto.tata.cor", "r");
    cr_assert_not_null(check);
    if (check)
        fclose(check);
    if (fd != -1)
        close(fd);
    system("rm -rf toto.tata.cor");
}

Test(Test_5, get_instruction_1)
{
    char *line = my_strdup("live %1");
    ins_node_t *node = init_ins_node();
    labelizer_t labels = {NULL, 0};
    int *value = NULL;

    cr_assert_eq(true, get_instruction(node, line, &labels));
    cr_assert_eq(node->id, LIVE);
    cr_assert_eq(node->args[0].type, DIR);
    value = node->args[0].value;
    cr_assert_eq(sizeof(*value), 4);
    cr_assert_eq(*value, 1);
}

Test(Test_6, get_instruction_2, .init = redirect_all_std)
{
    char *line = my_strdup("livee %1");
    ins_node_t *node = init_ins_node();
    labelizer_t labels = {NULL, 0};

    cr_assert_eq(false, get_instruction(node, line, &labels));
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Invalid instruction.\n");
    cr_assert_eq(UNKNOW, node->id);
    cr_assert_null(node->args);
}

Test(Test_7, get_instruction_3)
{
    char *line = my_strdup("lldi 34, %:l2, r1");
    ins_node_t *node = init_ins_node();
    short *ind = NULL;
    char *lab = NULL;
    char *reg = NULL;
    labelizer_t labels[2] = {{"l2", 0}, {NULL, 0}};

    cr_assert_eq(true, get_instruction(node, line, labels));
    cr_assert_eq(LLDI, node->id);
    cr_assert_eq(node->args[0].type, IND);
    cr_assert_eq(node->args[1].type, DIR_LAB);
    cr_assert_eq(node->args[2].type, REG);
    ind = node->args[0].value;
    cr_assert_eq(sizeof(*ind), 2);
    cr_assert_eq(*ind, 34);
    lab = node->args[1].value;
    cr_assert_str_eq(lab, "l2");
    reg = node->args[2].value;
    cr_assert_eq(sizeof(*reg), 1);
    cr_assert_eq(*reg, 1);
}

Test(Test_8, handle_header_name_1)
{
    char *line = my_strdup(".name \"zork\"");
    header_t header;
    h_error_t h_error = {false, false, false};

    cr_assert_eq(handle_header_name(line, &header, &h_error), true);
    cr_assert_eq(h_error.name_catch, true);
    cr_assert_eq(h_error.prev_was_name, true);
    cr_assert_eq(h_error.comment_catch, false);
    cr_assert_str_eq(header.prog_name, "zork");
}

Test(Test_9, handle_header_name_2, .init = redirect_all_std)
{
    char *line = my_strdup(".name     ");
    header_t header;
    h_error_t h_error = {false, false, false};

    cr_assert_eq(handle_header_name(line, &header, &h_error), false);
    cr_assert_eq(h_error.name_catch, false);
    cr_assert_eq(h_error.prev_was_name, false);
    cr_assert_eq(h_error.comment_catch, false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Syntax.\n");
}

Test(Test_11, handle_header_comment_1, .init = redirect_all_std)
{
    char *line = my_strdup(".comment \"hello\"");
    header_t header;
    h_error_t h_error = {false, false, false};

    cr_assert_eq(handle_header_comment(line, &header, &h_error), false);
    cr_assert_eq(h_error.name_catch, false);
    cr_assert_eq(h_error.prev_was_name, false);
    cr_assert_eq(h_error.comment_catch, false);
    cr_assert_stderr_eq_str(
        "[1m[31mError:[0m[0m Prog comment must "
        "be just after prog name.\n");
}

Test(Test_12, handle_header_comment_2)
{
    char *line = str_clean(my_strdup(".comment \"  hello \t wolrd  \""));
    header_t header;
    h_error_t h_error = {true, false, true};

    cr_assert_eq(handle_header_comment(line, &header, &h_error), true);
    cr_assert_eq(h_error.name_catch, true);
    cr_assert_eq(h_error.prev_was_name, false);
    cr_assert_eq(h_error.comment_catch, true);
}
