/*
** EPITECH PROJECT, 2019
** file_parsing.c
** File description:
** parse source file
*/

#include "my_print.h"
#include "tools.h"
#include "asm.h"

static void jump_to_first_ins(FILE *src, bool comment_catch)
{
    line_type_t stop = (comment_catch ? H_COM : H_NAME);
    char *line = NULL;
    line_type_t current = 0;

    fseek(src, 0, SEEK_SET);
    while ((line = read_file(src)) && current != stop) {
        current = get_line_type(line);
        free(line);
        line = NULL;
    }
    if (line)
        free(line);
}

char *read_file(FILE *src)
{
    char *buf = NULL;
    char *line = NULL;
    size_t n = 0;

    if (getline(&buf, &n, src) == -1 || !buf) {
        if (buf)
            free(buf);
        return NULL;
    }
    if (buf[my_strlen(buf) - 1] == '\n')
        buf[my_strlen(buf) - 1] = '\0';
    remove_comment(buf);
    line = str_clean(buf);
    free(buf);
    return line;
}

bool get_header_elem(parser_t *parser, FILE *src)
{
    char *line = NULL;
    line_type_t current = 0;
    bool feedback = true;

    while ((line = read_file(src))) {
        current = get_line_type(line);
        if (current < 2)
            feedback = fn_ptr[current](
                line, &parser->header, &parser->h_error);
        free(line);
        if (current == INS)
            break;
        if (!feedback) return false;
    }
    if (!parser->h_error.name_catch)
        return put_error("Prog name must be specified.") - 84;
    if (!parser->h_error.comment_catch)
        put_warning("No comment specified.");
    jump_to_first_ins(src, parser->h_error.comment_catch);
    return true;
}

parser_t *parse_file(FILE *src)
{
    parser_t *parser = init_parser();

    if (!parser)
        return NULL;
    if (!(parser->labels = pre_parsing(src, &parser->header.prog_size))) {
        free(parser);
        put_error("Pre-parsing failed.");
        return NULL;
    } if (!get_header_elem(parser, src)) {
        free(parser);
        return NULL;
    } if (!(parser->head = parse_instruction(src, parser->labels))) {
        free(parser);
        return NULL;
    }
    return parser;
}
