/*
** EPITECH PROJECT, 2019
** instructions.h
** File description:
** Corewar
*/

#ifndef INSTRUCTIONS_H_
    #define INSTRUCTIONS_H_

int get_arg_type(char coding_byte, int param_index);
int modify_carry(prog_t *prog, const bool on);
bool is_reg_exist(const int reg);
int live(vm_t *vm, prog_t *prog);
int add(vm_t *vm, prog_t *prog);
int sub(vm_t *vm, prog_t *prog);
int ld(vm_t *vm, prog_t *prog);
int st(vm_t *vm, prog_t *prog);
int and(vm_t *vm, prog_t *prog);
int and_reg_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int and_dir_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int and_ind_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int or(vm_t *vm, prog_t *prog);
int or_reg_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int or_dir_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int or_ind_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int xor(vm_t *vm, prog_t *prog);
int xor_reg_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int xor_dir_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int xor_ind_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int zjmp(vm_t *vm, prog_t *prog);
int ldi(vm_t *vm, prog_t *prog);
int ldi_reg_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int ldi_dir_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int ldi_ind_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int sti(vm_t *vm, prog_t *prog);
int sti_reg_reg_all(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int sti_reg_dir_all(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int sti_reg_ind_all(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int my_fork(vm_t *vm, prog_t *prog);
int lld(vm_t *vm, prog_t *prog);
int lldi(vm_t *vm, prog_t *prog);
int lldi_reg_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int lldi_dir_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int lldi_ind_all_reg(vm_t *vm, prog_t *prog, args_type_t arg[3]);
int my_lfork(vm_t *vm, prog_t *prog);
int aff(vm_t *vm, prog_t *prog);

#endif /* !INSTRUCTIONS_H_ */
