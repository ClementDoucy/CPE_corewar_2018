/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** execute_processes
*/

#include "corewar.h"
#include "instructions.h"

static int (* const instructions[16])(vm_t *, prog_t *) =
{
                                live,
                                ld,
                                st,
                                add,
                                sub,
                                and,
                                or,
                                xor,
                                zjmp,
                                ldi,
                                sti,
                                my_fork,
                                lld,
                                lldi,
                                my_lfork,
                                aff
};

static void schedule_instruction(vm_t *vm, prog_t *p)
{
    int target = vm->mem[p->pc];

    while (target < 1 || target > 16) {
        p->pc = (p->pc + 1) % MEM_SIZE;
        target = vm->mem[p->pc];
    }
    p->instruction = vm->mem[p->pc];
    p->clock = op_tab[p->instruction - 1].nbr_cycles - 1;
}

void execute_processes(vm_t *vm)
{
    for (prog_t *p = vm->head_champions; p != NULL; p = p->next) {
        p->pc = (p->pc < 0) ? ((p->pc % MEM_SIZE) + MEM_SIZE) : (p->pc);
        if (p->clock > 0)
            p->clock -= 1;
        if (p->instruction == 0) {
            schedule_instruction(vm, p);
        } else if (p->clock == 0) {
            instructions[p->instruction - 1](vm, p);
            p->instruction = 0;
        }
    }
}