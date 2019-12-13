/*
** EPITECH PROJECT, 2019
** corewar.h
** File description:
** corewar
*/

#ifndef COREWAR_H_
    #define COREWAR_H_

#include <stdlib.h>
#include <stdbool.h>
#include "op.h"

typedef struct champion
{
    int fd;
    int number;
    int address;
    char *name;
    int prog_size;
    char *comment;
} champion_t;

typedef struct program_s
{
    int pc;
    int instruction;
    bool carry;
    unsigned int r[REG_NUMBER];
    unsigned int clock;
    struct program_s *next;
    bool said_live;
    champion_t *infos;
} prog_t;

typedef struct game
{
    int dump;
    int nb_champions;
    champion_t **champions;
} game_t;

typedef struct cycle_s
{
    unsigned int p_alive;
    unsigned int cycle;
    int winner;
    int nbr_live;
} cycle_t;

typedef struct vm_s
{
    unsigned char *mem;
    game_t *infos;
    prog_t *head_champions;
    cycle_t cy;
} vm_t;

int usage(const char *filename);
/* PARSING */
//recup_dump_number.c
int recup_dump_number(game_t *game, char **av);
//recup_options.c
game_t *create_game(void);
void free_game(game_t *game);
game_t *recup_options(int ac, char **av);
//create_champion.c
int create_champion(game_t *game, int id, char **av, int i);
//recup_prog_number.c
int recup_prog_number(game_t *game, int id, char **av, int i);
//recup_load_address.c
int recup_load_address(game_t *game, int id, char **av, int i);

int recup_prog_name(champion_t *champion, char **av, int i);
//check_options_correct.c
int check_options_correct(game_t *game);
//define_default_options.c
int define_default_options(game_t *game);
//define_default_address.c
int define_default_address(game_t *game);
//define_default_number.c
int define_default_number(game_t *game);
//error_no_argument.c
int error_no_argument(char *filename);
//check_header.c
int check_header(champion_t *champion, char *av);
void dump_mem(vm_t *vm);
void destroy_vm(vm_t *vm);
void update_cycle(vm_t *vm, unsigned int *cycle_to_die);
int load_program(vm_t *vm, champion_t *champ);
prog_t *new_champion(champion_t *desc);
prog_t *init_champions(game_t *game);
int set_champions_in_mem(vm_t *vm);
vm_t *init_corewar(game_t *game);
void execute_processes(vm_t *vm);
int start_corewar(game_t *game);
void display_winner(vm_t *vm);

#endif /* !COREWAR_H_ */
