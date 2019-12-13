/*
** EPITECH PROJECT, 2019
** launcher.c
** File description:
** launcher for asm
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include "my_print.h"
#include "asm.h"

int create_bin_file(char *filepath)
{
    int bin = 0;
    char *bin_name = NULL;
    int size = (int)my_strlen(filepath);

    for (; size >= 0 && filepath[size] != '.'; size--);
    size += (size == -1 ? 1 : 0);
    if (filepath[size] == '.' && are_eq_str(&filepath[size], ".s")) {
        filepath[size] = '\0';
        bin_name = my_strcat(filepath, ".cor");
    } else
        bin_name = my_strcat(filepath, ".cor");
    if (!bin_name) {
        put_error("Malloc failed.");
        return -1;
    }
    bin = open(bin_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    free(bin_name);
    if (bin == -1)
        put_error("Can't create binary file.");
    return bin;
}

int failure(FILE *src, int bin, parser_t *parser, const char *msg)
{
    if (src)
        fclose(src);
    if (bin != -1)
        close(bin);
    if (parser) {
        destroy_ins_list(parser->head, NULL);
        free(parser);
    }
    return put_error(msg);
}

int success(FILE *src, int bin, parser_t *parser)
{
    if (src)
        fclose(src);
    if (bin != -1)
        close(bin);
    destroy_ins_list(parser->head, NULL);
    for (int i = 0; parser->labels && parser->labels[i].label; i++)
        free(parser->labels[i].label);
    if (parser->labels)
        free(parser->labels);
    free(parser);
    return 0;
}

static void check_filepath(char **filepath)
{
    int i = 0;
    int last_slash = 0;

    for (; (*filepath)[i]; i++)
        if ((*filepath)[i] == '/')
            last_slash = i;
    if (last_slash)
        (*filepath) += ++last_slash;
}

int launch(char *filepath)
{
    FILE *src = NULL;
    int bin = 0;
    parser_t *parser = NULL;

    if (!(src = fopen(filepath, "r")))
        return failure(src, bin, parser, "invalid file path.");
    if (!(parser = parse_file(src)))
        return failure(src, bin, parser, NULL);
    fclose(src);
    src = NULL;
    check_filepath(&filepath);
    if ((bin = create_bin_file(filepath)) == -1)
        return failure(src, bin, parser, NULL);
    if (!(write_bytecode(bin, parser)))
        return failure(src, bin, parser, "write system call failed.");
    return success(src, bin, parser);
}
