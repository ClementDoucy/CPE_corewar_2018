/*
** EPITECH PROJECT, 2019
** enum.h
** File description:
** header file for enum
*/

#pragma once

typedef enum line_type line_type_t;
typedef enum ins_id ins_id_t;
typedef enum param_type param_type_t;
typedef enum error_type err_type_t;

enum line_type {
    H_NAME,
    H_COM,
    INS,
    EMPTY,
    COM
};

enum error_type {
    EMPTY_LINE = -42,
    ARG_NB = -43,
    ARG_TYPE = -44,
    UNKNOW_INSTRUCTION = -45,
    DOUBLE_LABEL = -46,
    INVALID_LABEL = -47,
    NO_INSTRUCTION = -48
};

enum ins_id {
    UNKNOW = -1,
    LIVE,
    LD,
    ST,
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    ZJMP,
    LDI,
    STI,
    FORK,
    LLD,
    LLDI,
    LFORK,
    AFF
};

enum param_type {
    REG,
    DIR,
    IND,
    DIR_LAB,
    IND_LAB
};
