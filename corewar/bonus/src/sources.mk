##
## EPITECH PROJECT, 2019
## Corewar
## File description:
## Makefile sources
##

SRC_DIR			=	./src/

PARSING_DIR		=	parsing/

DEFAULT_PARSE	=	default/

VM_DIR			=	vm/

INSTRUC_DIR		=	instructions/

SRCS	+=	$(SRC_DIR)main.c
SRCS	+=	$(SRC_DIR)op.c
SRCS	+=	$(SRC_DIR)$(DEFAULT_PARSE)define_default_options.c
SRCS	+=	$(SRC_DIR)$(DEFAULT_PARSE)define_default_address.c
SRCS	+=	$(SRC_DIR)$(DEFAULT_PARSE)define_default_number.c
SRCS	+=	$(SRC_DIR)$(PARSING_DIR)error_no_argument.c
SRCS	+=	$(SRC_DIR)$(PARSING_DIR)usage.c
SRCS	+=	$(SRC_DIR)$(PARSING_DIR)recup_options.c
SRCS	+=	$(SRC_DIR)$(PARSING_DIR)recup_dump_number.c
SRCS	+=	$(SRC_DIR)$(PARSING_DIR)create_champion.c
SRCS	+=	$(SRC_DIR)$(PARSING_DIR)check_header.c
SRCS	+=	$(SRC_DIR)$(PARSING_DIR)recup_prog_number.c
SRCS	+=	$(SRC_DIR)$(PARSING_DIR)recup_load_address.c
SRCS	+=	$(SRC_DIR)$(PARSING_DIR)check_options_correct.c
SRCS	+=	$(SRC_DIR)$(VM_DIR)/dump_mem.c
SRCS	+=	$(SRC_DIR)$(VM_DIR)/init_corewar.c
SRCS	+=	$(SRC_DIR)$(VM_DIR)/load_program.c
SRCS	+=	$(SRC_DIR)$(VM_DIR)/set_champion.c
SRCS	+=	$(SRC_DIR)$(VM_DIR)/start_corewar.c
SRCS	+=	$(SRC_DIR)$(VM_DIR)/destroy_vm.c
SRCS	+=	$(SRC_DIR)$(VM_DIR)/update_cycle.c
SRCS	+=	$(SRC_DIR)$(VM_DIR)/display_winner.c
SRCS	+=	$(SRC_DIR)$(VM_DIR)/execute_processes.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)instruction_utils.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)live.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)ld.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)lld.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)st.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)add.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)sub.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)and.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)and_dir.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)and_ind.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)and_reg.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)or.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)or_dir.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)or_ind.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)or_reg.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)xor.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)xor_dir.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)xor_ind.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)xor_reg.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)zjmp.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)ldi.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)ldi_reg.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)ldi_dir.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)ldi_ind.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)lldi.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)lldi_reg.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)lldi_dir.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)lldi_ind.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)sti.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)sti_reg.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)sti_dir.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)sti_ind.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)fork.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)lfork.c
SRCS	+=	$(SRC_DIR)$(INSTRUC_DIR)aff.c
