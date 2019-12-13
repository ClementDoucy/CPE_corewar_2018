/*
** EPITECH PROJECT, 2019
** op.c
** File description:
** contains wonderfull op_tab
*/

#include "op.h"

const op_t op_tab[] =
{
    {"live", 1, {T_DIR}, 1, 10, "alive", 4, false},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 4, true},
    {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 4, true},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 4, true},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 4, true},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
        "et (and  r1, r2, r3   r1&r2 -> r3", 4, true},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
        "ou  (or   r1, r2, r3   r1 | r2 -> r3", 4, true},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
        "ou (xor  r1, r2, r3   r1^r2 -> r3", 4, true},
    {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 2, false},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
        "load index", 2, true},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
        "store index", 2, true},
    {"fork", 1, {T_DIR}, 12, 800, "fork", 2, false},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 4, true},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
        "long load index", 2, true},
    {"lfork", 1, {T_DIR}, 15, 1000, "long fork", 2, false},
    {"aff", 1, {T_REG}, 16, 2, "aff", 2, true},
    {0, 0, {0}, 0, 0, 0, 0, false},
};
