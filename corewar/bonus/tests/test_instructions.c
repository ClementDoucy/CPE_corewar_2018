/*
** EPITECH PROJECT, 2018
** tests unitaires
** File description:
** criterion tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "corewar.h"
#include "mystring.h"
#include "instructions.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static champion_t *create_champion_test(void)
{
    champion_t *champion = malloc(sizeof(champion_t));

    if (!champion)
        return NULL;
    champion->fd = -1;
    champion->number = 1;
    champion->address = 0;
    if (!(champion->name = my_strdup("test_name")))
        return NULL;
    champion->prog_size = 100;
    champion->comment = NULL;
    return champion;
}

static prog_t *create_process_test(void)
{
    prog_t *process = malloc(sizeof(prog_t));

    if (!process)
        return NULL;
    process->pc = 0;
    process->carry = false;
    process->r[0] = 1;
    for (int i = 1; i < REG_NUMBER; i++)
        process->r[i] = 0;
    process->clock = -1;
    process->next = NULL;
    process->infos = create_champion_test();
    return process;
}

static vm_t *create_vm_test(void)
{
    vm_t *vm = malloc(sizeof(vm_t));

    if (!vm)
        return NULL;
    if (!(vm->mem = malloc(sizeof(char) * MEM_SIZE)))
        return NULL;
    my_memset(vm->mem, 0, MEM_SIZE);
    vm->infos = NULL;
    if (!(vm->head_champions = create_process_test()))
        return NULL;
    return vm;
}

static void destroy_vm_test(vm_t *vm)
{
    free(vm->head_champions->infos->name);
    free(vm->head_champions->infos);
    free(vm->head_champions);
    free(vm->mem);
    free(vm);
}

Test(get_arg_type, test_reg_1)
{
    char coding_byte = 0b01011000;
    int param_index = 1;
    int return_value = get_arg_type(coding_byte, param_index);

    cr_assert_eq(return_value, T_REG);
}

Test(get_arg_type, test_dir_2)
{
    char coding_byte = 0b01101000;
    int param_index = 2;
    int return_value = get_arg_type(coding_byte, param_index);

    cr_assert_eq(return_value, T_DIR);
}

Test(get_arg_type, test_ind_3)
{
    char coding_byte = 0b01011100;
    int param_index = 3;
    int return_value = get_arg_type(coding_byte, param_index);

    cr_assert_eq(return_value, T_IND);
}

Test(get_arg_type, test_false)
{
    char coding_byte = 0b01011000;
    int param_index = 4;
    int return_value = get_arg_type(coding_byte, param_index);

    cr_assert_eq(return_value, 84);
}

Test(modify_carry, change_carry_to_true)
{
    prog_t *prog = malloc(sizeof(prog_t));
    int return_value = 0;

    if (!prog)
        return;
    prog->carry = true;
    return_value = modify_carry(prog, true);
    cr_assert_eq(prog->carry, true);
    cr_assert_eq(return_value, 0);
    free(prog);
}

Test(modify_carry, change_carry_to_false)
{
    prog_t *prog = malloc(sizeof(prog_t));
    int return_value = 0;

    if (!prog)
        return;
    prog->carry = true;
    return_value = modify_carry(prog, false);
    cr_assert_eq(prog->carry, false);
    cr_assert_eq(return_value, 0);
    free(prog);
}

Test(is_reg_exist, test_all_in_one)
{
    for (int i = 1; i <= REG_NUMBER; i++)
        cr_assert_eq(is_reg_exist(i), true);
    cr_assert_eq(is_reg_exist(0), false);
    cr_assert_eq(is_reg_exist(17), false);
    cr_assert_eq(is_reg_exist(-8621), false);
    cr_assert_eq(is_reg_exist(8621), false);
}

Test(ld, load_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x02900000, 0x00640200};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ld(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[1], 100);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(ld, load_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x02900000, 0x00641700};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ld(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(ld, load_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x02d00003, 0x0a000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ld(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[9], 0x030a0000);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(ld, load_ind_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x02d00003, 0x17000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ld(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[9], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(ld, load_ind_reg_false_bad_coding_byte)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x02aa0003, 0x17000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ld(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[9], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(st, store_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x03500104, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = st(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[3], vm->head_champions->r[0]);
    cr_assert_eq(vm->head_champions->pc, 4);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(st, store_reg_reg_false_invalid_register)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x03500117, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = st(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[3], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(st, store_reg_ind_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x03700304, 0x0a000000};
    int return_value = 0;

    if (!vm)
        return;
    vm->head_champions->r[2] = 0x12345678;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = st(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->mem[10], 0x12);
    cr_assert_eq(vm->mem[11], 0x34);
    cr_assert_eq(vm->mem[12], 0x56);
    cr_assert_eq(vm->mem[13], 0x78);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(st, store_false_bad_register)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x03501702, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = st(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[3], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(st, store_false_bad_coding_byte)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x03550205, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = st(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[3], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(add, addition_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x04540102, 0x06000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = add(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[5], 1);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(add, addition_true_with_largest_nb)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x04540102, 0x06000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    vm->head_champions->r[1] = 2147483647;
    return_value = add(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 2147483647);
    cr_assert_eq(vm->head_champions->r[5], 2147483648);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(add, addition_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x04540123, 0x06000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = add(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[5], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(add, addition_false_bad_coding_byte)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x04aa0107, 0x06000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = add(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[5], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sub, substraction_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x05540102, 0x06000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sub(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[5], 1);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(sub, substraction_true_with_largest_nb)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0554010e, 0x06000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    vm->head_champions->r[13] = 2147483647;
    return_value = sub(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[13], 2147483647);
    cr_assert_eq(vm->head_champions->r[5], -2147483646);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(sub, substraction_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x05540123, 0x06000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sub(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[5], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sub, substraction_false_bad_coding_byte)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x05aa0107, 0x06000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sub(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[5], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_dir_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06a40000, 0x00020000, 0x00040800};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 2 & 4);
    cr_assert_eq(vm->head_champions->pc, 11);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(and, and_dir_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06a40000, 0x00020000, 0x0004aa00};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_dir_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06940000, 0x00020408, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x1234;
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 2 & vm->head_champions->r[3]);
    cr_assert_eq(vm->head_champions->pc, 8);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(and, and_dir_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06940000, 0x00020423, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x1234;
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_dir_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06b40000, 0x00170004, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x17 & 0x00170004);
    cr_assert_eq(vm->head_champions->pc, 9);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(and, and_dir_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06b40000, 0x00020004, 0x23000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_ind_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06d40004, 0x06080000, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[5] = 0x1234;
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x1234 & 0x06080000);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(and, and_ind_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06d40004, 0x06230000, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_ind_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06e40006, 0x00000006, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00060800 & 6);
    cr_assert_eq(vm->head_champions->pc, 9);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(and, and_ind_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06e40006, 0x00000006, 0x23000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_ind_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06f40004, 0x00060800, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00060800 & 0x08000000);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(and, and_ind_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06f40004, 0x00062300, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_reg_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06540406, 0x08000000, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    for (int i = 0; i < 3; i++)
        instruction[i] = convert_endian_number(instruction[i]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x73649872;
    vm->head_champions->r[5] = 0x62148391;
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7],
        vm->head_champions->r[3] & vm->head_champions->r[5]);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
}

Test(and, and_reg_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06542306, 0x23000000, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_reg_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06640400, 0x00000608, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x73649872;
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], vm->head_champions->r[3] & 0x6);
    cr_assert_eq(vm->head_champions->pc, 8);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(and, and_reg_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06740400, 0x03080000, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x73649872;
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], vm->head_champions->r[3] & 0x30800);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(and, and_reg_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06742300, 0x00000623, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_reg_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06642300, 0x00000623, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(and, and_reg_dir_reg_false_arg2_is_not_register)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x06302300, 0x00000623, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(or, and_dir_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07a40000, 0x00020000, 0x00040800};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 2 | 4);
    cr_assert_eq(vm->head_champions->pc, 11);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(or, and_dir_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07a40000, 0x00020000, 0x0004aa00};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(or, and_dir_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07940000, 0x00020408, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x1234;
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 2 | vm->head_champions->r[3]);
    cr_assert_eq(vm->head_champions->pc, 8);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(or, and_dir_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07940000, 0x00020423, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x1234;
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(or, and_dir_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07b40000, 0x00170004, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x17 | 0x00170004);
    cr_assert_eq(vm->head_champions->pc, 9);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(or, and_dir_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07b40000, 0x00020004, 0x23000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(or, and_ind_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07d40004, 0x06080000, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[5] = 0x1234;
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x1234 | 0x06080000);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
}

Test(or, and_ind_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07d40004, 0x06230000, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(or, and_ind_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07e40006, 0x00000006, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00060800 | 6);
    cr_assert_eq(vm->head_champions->pc, 9);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(or, and_ind_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07e40006, 0x00000006, 0x23000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(or, and_ind_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07f40004, 0x00060800, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00060800 | 0x08000000);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(or, and_ind_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07f40004, 0x00062300, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(or, and_reg_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07540406, 0x08000000, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    for (int i = 0; i < 3; i++)
        instruction[i] = convert_endian_number(instruction[i]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x73649872;
    vm->head_champions->r[5] = 0x62148391;
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], vm->head_champions->r[3] |
            vm->head_champions->r[5]);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
}

Test(or, and_reg_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07542306, 0x23000000, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(or, and_reg_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07640400, 0x00000608, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x73649872;
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], vm->head_champions->r[3] | 0x6);
    cr_assert_eq(vm->head_champions->pc, 8);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(or, and_reg_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07740400, 0x04080000, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    for (int i = 0; i < 3; i++)
        instruction[i] = convert_endian_number(instruction[i]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x73649872;
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], vm->head_champions->r[3] |
                0x4080000);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(or, and_reg_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07740400, 0x04180000, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(or, and_reg_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x07640400, 0x00000618, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = or(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(xor, and_dir_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08a40000, 0x00020000, 0x00040800};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 2 ^ 4);
    cr_assert_eq(vm->head_champions->pc, 11);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(xor, and_dir_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08a40000, 0x00020000, 0x0004aa00};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(xor, and_dir_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08940000, 0x00020408, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x1234;
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 2 ^ vm->head_champions->r[3]);
    cr_assert_eq(vm->head_champions->pc, 8);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(xor, and_dir_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08940000, 0x00020423, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x1234;
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(xor, and_dir_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08b40000, 0x00170004, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x17 ^ 0x00170004);
    cr_assert_eq(vm->head_champions->pc, 9);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(xor, and_dir_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08b40000, 0x00020004, 0x23000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(xor, and_ind_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08d40004, 0x06080000, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[5] = 0x1234;
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x1234 ^ 0x06080000);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(xor, and_ind_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08d40004, 0x06230000, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(xor, and_ind_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08e40006, 0x00000006, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00060800 ^ 6);
    cr_assert_eq(vm->head_champions->pc, 9);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(xor, and_ind_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08e40006, 0x00000006, 0x23000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(xor, and_ind_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08f40004, 0x00060800, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00060800 ^ 0x08000000);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(xor, and_ind_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08f40004, 0x00062300, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(xor, and_reg_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08540406, 0x08000000, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    for (int i = 0; i < 3; i++)
        instruction[i] = convert_endian_number(instruction[i]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x73649872;
    vm->head_champions->r[5] = 0x62148391;
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], vm->head_champions->r[3] ^
    vm->head_champions->r[5]);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
}

Test(xor, and_reg_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08542306, 0x23000000, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(xor, xor_reg_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08640400, 0x00000608, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x73649872;
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], vm->head_champions->r[3] ^ 6);
    cr_assert_eq(vm->head_champions->pc, 8);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(xor, xor_reg_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08740400, 0x03080000, 0x00000000};
    int return_value = 0;
    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->r[3] = 0x73649872;
    return_value = xor(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], vm->head_champions->r[3] ^ 0x30800);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(xor, xor_reg_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08742300, 0x00000623, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(xor, xor_reg_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x08642300, 0x00000623, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = and(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[0], 1);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(zjmp, zjmp_with_carry_equal_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x09002b00, 0x00000000, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->carry = true;
    return_value = zjmp(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->pc, 43);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(zjmp, zjmp_with_carry_equal_false)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x09002b00, 0x00000000, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    vm->head_champions->carry = false;
    return_value = zjmp(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->pc, 3);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_reg_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0a640100, 0x03080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x03080000);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_reg_dir_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0a641700, 0x03080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_reg_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0a540103, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x54010308);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_reg_reg_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0a541703, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_dir_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x0aa40001, 0x00030800, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00030800);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_dir_dir_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x0aa40000, 0x00010000, 0x00031700};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_dir_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0a940001, 0x03080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x94000103);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_dir_reg_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0a940001, 0x23080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_ind_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x0ae40002, 0x00030800, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x03080000);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_ind_dir_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x0ae40002, 0x00031800, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_ind_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0ad40002, 0x03080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00020308);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_ind_reg_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0ad40001, 0x23080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(ldi, loadindex_false_bad_coding_byte)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0ad99001, 0x23080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_reg_dir_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b580103, 0x00050000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->mem[5], 0x0);
    cr_assert_eq(vm->mem[6], 0x0);
    cr_assert_eq(vm->mem[7], 0x0);
    cr_assert_eq(vm->mem[8], 0x1);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_reg_ind_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b581703, 0x00050000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->mem[5], 0x5);
    cr_assert_eq(vm->mem[6], 0x0);
    cr_assert_eq(vm->mem[7], 0x0);
    cr_assert_eq(vm->mem[8], 0x0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b540103, 0x05000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->mem[0], 0x0);
    cr_assert_eq(vm->mem[1], 0x0);
    cr_assert_eq(vm->mem[2], 0x0);
    cr_assert_eq(vm->mem[3], 0x1);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_reg_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b541703, 0x05000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->mem[4], 0x5);
    cr_assert_eq(vm->mem[5], 0x0);
    cr_assert_eq(vm->mem[6], 0x0);
    cr_assert_eq(vm->mem[7], 0x0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_dir_dir_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b680100, 0x03000500};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    vm->head_champions->r[0] = 0x98765432;
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->mem[8], 0x98);
    cr_assert_eq(vm->mem[9], 0x76);
    cr_assert_eq(vm->mem[10], 0x54);
    cr_assert_eq(vm->mem[11], 0x32);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_dir_dir_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b681700, 0x03000500};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    vm->head_champions->r[0] = 0x98765432;
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->mem[8], 0x0);
    cr_assert_eq(vm->mem[9], 0x0);
    cr_assert_eq(vm->mem[10], 0x0);
    cr_assert_eq(vm->mem[11], 0x0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b640100, 0x03050000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->mem[3], 0x0);
    cr_assert_eq(vm->mem[4], 0x0);
    cr_assert_eq(vm->mem[5], 0x0);
    cr_assert_eq(vm->mem[6], 0x1);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b641700, 0x03050000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->mem[3], 0x0);
    cr_assert_eq(vm->mem[4], 0x03);
    cr_assert_eq(vm->mem[5], 0x05);
    cr_assert_eq(vm->mem[6], 0x0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_ind_dir_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b780100, 0x03000500};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    vm->head_champions->r[0] = 0x98765432;
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->mem[8], 0x98);
    cr_assert_eq(vm->mem[9], 0x76);
    cr_assert_eq(vm->mem[10], 0x54);
    cr_assert_eq(vm->mem[11], 0x32);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_ind_dir_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b781700, 0x03000500};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    vm->head_champions->r[0] = 0x98765432;
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->mem[8], 0x0);
    cr_assert_eq(vm->mem[9], 0x0);
    cr_assert_eq(vm->mem[10], 0x0);
    cr_assert_eq(vm->mem[11], 0x0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b740100, 0x03050000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->mem[3], 0x0);
    cr_assert_eq(vm->mem[4], 0x0);
    cr_assert_eq(vm->mem[5], 0x0);
    cr_assert_eq(vm->mem[6], 0x1);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(sti, storeindex_reg_ind_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0b741700, 0x03050000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = sti(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->mem[3], 0x0);
    cr_assert_eq(vm->mem[4], 0x03);
    cr_assert_eq(vm->mem[5], 0x05);
    cr_assert_eq(vm->mem[6], 0x0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

static void check_my_fork_true(int return_value, vm_t *vm)
{
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->mem[0], 0x0c);
    cr_assert_eq(vm->mem[1], 0x00);
    cr_assert_eq(vm->mem[2], 0x0a);
    cr_assert_eq(vm->mem[3], 0x00);
    cr_assert_eq(vm->mem[10], 0x00);
    cr_assert_eq(vm->mem[11], 0x00);
    cr_assert_eq(vm->mem[12], 0x00);
    cr_assert_eq(vm->mem[13], 0x00);
    cr_assert_eq(vm->head_champions->pc, 3);
    cr_assert_eq(vm->head_champions->carry, false);
}

Test(my_fork, fork_true)
{
    vm_t *vm = create_vm_test();
    int instruction = 0x0c000a00;
    int return_value = 0;

    if (!vm)
        return;
    instruction = convert_endian_number(instruction);
    my_memcpy(&vm->mem[0], &instruction, 4);
    vm->head_champions->infos->fd = open("./cor/fork_test.cor", O_RDONLY);
    if (vm->head_champions->infos->fd == -1 || lseek(vm->head_champions->\
                infos->fd, sizeof(header_t), SEEK_SET) != sizeof(header_t))
        return;
    vm->head_champions->infos->prog_size = 0x03;
    return_value = my_fork(vm, vm->head_champions);
    check_my_fork_true(return_value, vm);
    close(vm->head_champions->infos->fd);
    destroy_vm_test(vm);
}

static void check_lfork_true(int return_value, vm_t *vm)
{
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->mem[0], 0x0f);
    cr_assert_eq(vm->mem[1], 0x00);
    cr_assert_eq(vm->mem[2], 0x0a);
    cr_assert_eq(vm->mem[3], 0x00);
    cr_assert_eq(vm->mem[10], 0x00);
    cr_assert_eq(vm->mem[11], 0x00);
    cr_assert_eq(vm->mem[12], 0x00);
    cr_assert_eq(vm->mem[13], 0x00);
    cr_assert_eq(vm->head_champions->pc, 3);
    cr_assert_eq(vm->head_champions->carry, false);
}

Test(my_lfork, lfork_true)
{
    vm_t *vm = create_vm_test();
    int instruction = 0x0f000a00;
    int return_value = 0;

    if (!vm)
        return;
    instruction = convert_endian_number(instruction);
    my_memcpy(&vm->mem[0], &instruction, 4);
    vm->head_champions->infos->fd = open("./cor/fork_test.cor", O_RDONLY);
    if (vm->head_champions->infos->fd == -1 || lseek(vm->head_champions->\
                infos->fd, sizeof(header_t), SEEK_SET) != sizeof(header_t))
        return;
    vm->head_champions->infos->prog_size = 0x03;
    return_value = my_lfork(vm, vm->head_champions);
    check_lfork_true(return_value, vm);
    close(vm->head_champions->infos->fd);
    destroy_vm_test(vm);
}

Test(lld, load_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0d900000, 0x00640200};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lld(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[1], 100);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(lld, load_dir_reg_false_reg_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0d900000, 0x00641700};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = ld(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[1], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(lld, load_ind_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0dd00003, 0x0a000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lld(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[9], 0x030a0000);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(lld, load_ind_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0dd00003, 0x17000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lld(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[9], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(lld, load_ind_reg_false_bad_coding_byte)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0daa0003, 0x17000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lld(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[9], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_reg_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0e640100, 0x03080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x03080000);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_reg_dir_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0e641700, 0x03080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_reg_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0e540103, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x54010308);
    cr_assert_eq(vm->head_champions->pc, 5);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_reg_reg_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0e541703, 0x08000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_dir_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x0ea40001, 0x00030800, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00030800);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_dir_dir_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x0ea40000, 0x00010000, 0x00031700};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_dir_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0e940001, 0x03080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x94000103);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_dir_reg_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0e940001, 0x23080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_ind_dir_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x0ee40002, 0x00030800, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    instruction[2] = convert_endian_number(instruction[2]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    my_memcpy(&vm->mem[8], &instruction[2], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x03080000);
    cr_assert_eq(vm->head_champions->pc, 7);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_ind_dir_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[3] = {0x0ee40002, 0x00031800, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_ind_reg_reg_true)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0ed40002, 0x03080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->r[7], 0x00020308);
    cr_assert_eq(vm->head_champions->pc, 6);
    cr_assert_eq(vm->head_champions->carry, true);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_ind_reg_reg_false_register_doesnt_exist)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0ed40001, 0x23080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(lldi, loadindex_false_bad_coding_byte)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x0ed99001, 0x23080000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = lldi(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->r[7], 0);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(aff, aff_true, .init=redirect_all_std)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x10400200, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    vm->head_champions->r[1] = 42;
    return_value = aff(vm, vm->head_champions);
    cr_assert_stdout_eq_str("*");
    cr_assert_eq(return_value, 0);
    cr_assert_eq(vm->head_champions->pc, 3);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(aff, aff_false_bad_coding_byte)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x10450200, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = aff(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}

Test(aff, aff_false_bad_register)
{
    vm_t *vm = create_vm_test();
    int instruction[2] = {0x10402300, 0x00000000};
    int return_value = 0;

    if (!vm)
        return;
    instruction[0] = convert_endian_number(instruction[0]);
    instruction[1] = convert_endian_number(instruction[1]);
    my_memcpy(&vm->mem[0], &instruction[0], 4);
    my_memcpy(&vm->mem[4], &instruction[1], 4);
    return_value = aff(vm, vm->head_champions);
    cr_assert_eq(return_value, 84);
    cr_assert_eq(vm->head_champions->pc, 0);
    cr_assert_eq(vm->head_champions->carry, false);
    destroy_vm_test(vm);
}
