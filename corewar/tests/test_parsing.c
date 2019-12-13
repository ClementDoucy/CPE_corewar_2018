/*
** EPITECH PROJECT, 2018
** tests
** File description:
** criterion tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "corewar.h"
#include "op.h"
#include "mystring.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(recup_dump_number, valid_test_with_dump)
{
    game_t *game = create_game();
    char *av[4] = {"./corewar", "-dump", "500", NULL};
    int return_value = 0;

    return_value = recup_dump_number(game, av);
    cr_assert_eq(game->dump, 500);
    cr_assert_eq(return_value, 3);
    free_game(game);
}

Test(recup_dump_number, valid_test_without_dump)
{
    game_t *game = create_game();
    char *av[4] = {"./corewar", "-n", "500", NULL};
    int return_value = 0;

    return_value = recup_dump_number(game, av);
    cr_assert_eq(game->dump, -1);
    cr_assert_eq(return_value, 1);
    free_game(game);
}

Test(recup_dump_number, invalid_test_no_argument, .init=redirect_all_std)
{
    game_t *game = create_game();
    char *av[3] = {"./corewar", "-dump", NULL};
    int return_value = 0;

    return_value = recup_dump_number(game, av);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str("-dump argument needs one argument\n");
    free_game(game);
}

Test(recup_dump_number, invalid_test_argument_false, .init=redirect_all_std)
{
    game_t *game = create_game();
    char *false_argument = "w";
    char *av[4] = {"./corewar", "-dump", false_argument, NULL};
    int return_value = 0;

    return_value = recup_dump_number(game, av);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str(
            "-dump argument w is invalid. Please enter a positive number.\n");
    free_game(game);
}

Test(recup_dump_number, invalid_test_argument_negative, .init=redirect_all_std)
{
    game_t *game = create_game();
    char *false_argument = "-13";
    char *av[4] = {"./corewar", "-dump", false_argument, NULL};
    int return_value = 0;

    return_value = recup_dump_number(game, av);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str(
            "-dump argument -13 is invalid. Please enter a positive number.\n");
    free_game(game);
}

Test(recup_load_address, test_true)
{
    game_t *game = create_game();
    char *av[5] = {"./corewar", "-a", "1234", "cor/abel.cor", NULL};
    int i = 1;

    i = recup_load_address(game, 0, av, i);
    cr_assert_eq(game->champions[0]->address, 1234);
    cr_assert_eq(i, 3);
    free_game(game);
}

Test(recup_load_address, test_false_address_in_hexa_simple,
        .init=redirect_all_std)
{
    game_t *game = create_game();
    int ac = 4;
    char *av[5] = {"./corewar", "-a", "0x", "cor/abel.cor", NULL};
    int i = 1;

    i = recup_load_address(game, 0, av, i);
    cr_assert_eq(i, -84);
    cr_assert_stderr_eq_str("-a argument 0x is invalid.\n\
Enter a positive number.\n");
    free_game(game);
}

Test(recup_load_address, test_false_address_in_hexa_invalid_char,
        .init=redirect_all_std)
{
    game_t *game = create_game();
    int ac = 4;
    char *av[5] = {"./corewar", "-a", "0xv", "cor/abel.cor", NULL};
    int i = 1;

    i = recup_load_address(game, 0, av, i);
    cr_assert_eq(i, -84);
    cr_assert_stderr_eq_str("-a argument 0xv is invalid.\n\
Enter a positive number.\n");
    free_game(game);
}

Test(recup_load_address, test_false_no_number_after_argument,
        .init=redirect_all_std)
{
    game_t *game = create_game();
    char *av[3] = {"./corewar", "-a", NULL};
    int i = 1;

    i = recup_load_address(game, 0, av, i);
    cr_assert_eq(i, -84);
    cr_assert_stderr_eq_str("-a argument needs one argument\n");
    free_game(game);
}

Test(recup_load_address, test_false_invalid_argument_after_a,
        .init=redirect_all_std)
{
    game_t *game = create_game();
    char *av[5] = {"./corewar", "-a", "invalid", "cor/abel.cor", NULL};
    int i = 1;

    i = recup_load_address(game, 0, av, i);
    cr_assert_eq(i, -84);
    cr_assert_stderr_eq_str("-a argument invalid is invalid.\n\
Enter a positive number.\n");
    free_game(game);
}

Test(recup_load_address, test_false_negative_argument_after_a,
        .init=redirect_all_std)
{
    game_t *game = create_game();
    char *av[5] = {"./corewar", "-a", "-10", "cor/abel.cor", NULL};
    int i = 1;

    i = recup_load_address(game, 0, av, i);
    cr_assert_eq(i, -84);
    cr_assert_stderr_eq_str("-a argument -10 is invalid.\n\
Enter a positive number.\n");
    free_game(game);
}


Test(usage, test_usage, .init=redirect_all_std)
{
    int return_value = usage("bonjour");

    cr_assert_eq(return_value, 0);
}

Test(recup_prog_number, test_good_prog_number_return_value)
{
    game_t *game = create_game();
    char *av[4] = {"./corewar", "-n", "1", NULL};
    int return_value;

    return_value = recup_prog_number(game, 0, av, 1);
    cr_assert_eq(return_value, 3);
    free_game(game);
}

Test(recup_prog_number, test_no_n_option)
{
    game_t *game = create_game();
    char *av[3] = {"./corewar", "1", NULL};
    int return_value;

    return_value = recup_prog_number(game, 0, av, 1);
    cr_assert_eq(return_value, 1);
    free_game(game);
}

Test(recup_prog_number, test_n_option_no_argument, .init=redirect_all_std)
{
    game_t *game = create_game();
    char *av[4] = {"./corewar", "-n", NULL};
    int return_value;

    return_value = recup_prog_number(game, 0, av, 1);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str("-n argument needs one argument\n");
    free_game(game);
}

Test(recup_prog_number, test_prog_nan, .init=redirect_all_std)
{
    game_t *game = create_game();
    char *av[4] = {"./corewar", "-n", "azer", NULL};
    int return_value;

    return_value = recup_prog_number(game, 0, av, 1);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str("-n argument azer is invalid.\n\
Enter a number between 1 and 4.\n");
    free_game(game);
}

Test(recup_prog_number, test_prog_number_out, .init=redirect_all_std)
{
    game_t *game = create_game();
    char *av[4] = {"./corewar", "-n", "5", NULL};
    int return_value;

    return_value = recup_prog_number(game, 0, av, 1);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str("-n argument 5 is invalid.\n\
Enter a number between 1 and 4.\n");
    free_game(game);
}

Test(recup_prog_number, test_prog_number_out_2, .init=redirect_all_std)
{
    game_t *game = create_game();
    char *av[4] = {"./corewar", "-n", "0", NULL};
    int return_value;

    return_value = recup_prog_number(game, 0, av, 1);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str("-n argument 0 is invalid.\n\
Enter a number between 1 and 4.\n");
    free_game(game);
}

Test(recup_prog_number, test_prog_number_out_3, .init=redirect_all_std)
{
    game_t *game = create_game();
    char *av[4] = {"./corewar", "-n", "-5", NULL};
    int return_value;

    return_value = recup_prog_number(game, 0, av, 1);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str("-n argument -5 is invalid.\n\
Enter a number between 1 and 4.\n");
    free_game(game);
}

Test(free_game, test_free_null_game)
{
    game_t *game = NULL;

    free_game(game);
}

Test(recup_options, test_no_options, .init=redirect_all_std)
{
    game_t *game = NULL;
    int ac = 2;
    char *av[3] = {"./corewar", "", NULL};
    void *return_value;

    return_value = recup_options(ac, av);
    cr_assert_eq(return_value, NULL);
    free_game(game);
}

Test(recup_options, test_too_many_players, .init=redirect_all_std)
{
    game_t *game = NULL;
    int ac = 6;
    char *av[7] = {"./corewar", "cor/abel.cor", "cor/abel.cor",
        "cor/abel.cor", "cor/abel.cor", "cor/abel.cor", NULL};
    void *return_value;

    return_value = recup_options(ac, av);
    cr_assert_eq(return_value, NULL);
    cr_assert_stderr_eq_str(
            "The number of champion load is above the limit.\n");
    free_game(game);
}

Test(recup_options, test_valid)
{
    game_t *game = NULL;
    int ac = 7;
    char *av[8] = {"./corewar", "-n", "1", "cor/abel.cor",
        "cor/abel.cor", "cor/abel.cor", "cor/abel.cor", NULL};

    game = recup_options(ac, av);
    cr_assert_eq(game->nb_champions, 4);
    cr_assert_eq(game->champions[0]->number, 1);
    cr_assert_eq(game->champions[1]->number, -1);
    cr_assert_eq(game->champions[2]->number, -1);
    cr_assert_eq(game->champions[3]->number, -1);
    free_game(game);
}

Test(create_game, valid_test)
{
    game_t *game = create_game();

    cr_assert_eq(game->dump, -1);
    cr_assert_eq(game->nb_champions, 0);
    free_game(game);
}

Test(define_default_number, test_true)
{
    game_t *game = NULL;
    int ac = 5;
    char *av[6] = {"./corewar", "cor/abel.cor", "cor/abel.cor",
        "cor/abel.cor", "cor/abel.cor", NULL};

    if (!(game = recup_options(ac, av)))
        return;
    game->champions[0]->number = define_default_number(game);
    cr_assert_eq(game->champions[0]->number, 1);
    game->champions[1]->number = define_default_number(game);
    cr_assert_eq(game->champions[1]->number, 2);
    game->champions[2]->number = define_default_number(game);
    cr_assert_eq(game->champions[2]->number, 3);
    game->champions[3]->number = define_default_number(game);
    cr_assert_eq(game->champions[3]->number, 4);
    free_game(game);
}

Test(define_default_number, test_false)
{
    game_t *game = NULL;
    int ac = 5;
    char *av[6] = {"./corewar", "cor/abel.cor", "cor/abel.cor",
        "cor/abel.cor", "cor/abel.cor", NULL};

    if (!(game = recup_options(ac, av)))
        return;
    game->champions[0]->number = define_default_number(game);
    game->champions[1]->number = define_default_number(game);
    game->champions[2]->number = define_default_number(game);
    game->champions[3]->number = define_default_number(game);
    game->champions[3]->number = define_default_number(game);
    cr_assert_eq(game->champions[3]->number, -84);
    free_game(game);
}

Test(check_options_correct, valid_test_all_number_different)
{
    game_t *game = create_game();
    int return_value = 0;

    game->nb_champions = 4;
    for (int i = 0; i < 4; i++)
        game->champions[i]->number = i + 1;
    return_value = check_options_correct(game);
    cr_assert_eq(return_value, 0);
    free_game(game);
}

Test(check_options_correct, valid_test_all_addresses_different)
{
    game_t *game = create_game();
    int return_value = 0;

    game->nb_champions = 4;
    for (int i = 0; i < 4; i++)
        game->champions[i]->address = i + 1;
    return_value = check_options_correct(game);
    cr_assert_eq(return_value, 0);
    free_game(game);
}

Test(check_options_correct, invalid_test_two_same_numbers,
        .init=redirect_all_std)
{
    game_t *game = create_game();
    int return_value = 0;

    game->nb_champions = 4;
    for (int i = 0; i < 4; i++)
        game->champions[i]->number = i + 1;
    game->champions[0]->number = 2;
    return_value = check_options_correct(game);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str("double definition of prog_number.\n");
    free_game(game);
}

Test(check_options_correct, invalid_test_two_same_addresses,
        .init=redirect_all_std)
{
    game_t *game = create_game();
    int return_value = 0;

    game->nb_champions = 4;
    for (int i = 0; i < 4; i++)
        game->champions[i]->address = i + 1;
    game->champions[0]->address = 2;
    return_value = check_options_correct(game);
    cr_assert_eq(return_value, -84);
    cr_assert_stderr_eq_str("double definition of load address.\n");
    free_game(game);
}

Test(error_no_argument, valid_test)
{
    cr_assert_eq(error_no_argument("bonjour"), 84);
}

Test(check_header, valid_test)
{
    champion_t *tmp = malloc(sizeof(champion_t));
    char *filename = "cor/abel.cor";
    tmp->fd = open(filename, O_RDONLY);

    if (!tmp || !tmp->fd)
        return;
    cr_assert_eq(check_header(tmp, filename), 0);
    close(tmp->fd);
    free(tmp);
}

Test(check_header, invalid_test_header_size_too_short, .init=redirect_all_std)
{
    champion_t *tmp = malloc(sizeof(champion_t));
    char *filename = "cor/incorrect_header_size.cor";
    tmp->fd = open(filename, O_RDONLY);

    if (!tmp || !tmp->fd)
        return;
    cr_assert_eq(check_header(tmp, filename), -84);
    cr_assert_stderr_eq_str(
            "cor/incorrect_header_size.cor is not an executable.\n");
    close(tmp->fd);
    free(tmp);
}

Test(check_header, invalid_test_header_magic_number_false,
        .init=redirect_all_std)
{
    champion_t *tmp = malloc(sizeof(champion_t));
    char *filename = "cor/incorrect_magic_number.cor";
    tmp->fd = open(filename, O_RDONLY);

    if (!tmp || !tmp->fd)
        return;
    cr_assert_eq(check_header(tmp, filename), -84);
    cr_assert_stderr_eq_str("Wrong executable magic number.\n");
    close(tmp->fd);
    free(tmp);
}

Test(check_header, invalid_test_header_prog_size_false, .init=redirect_all_std)
{
    champion_t *tmp = malloc(sizeof(champion_t));
    char *filename = "cor/incorrect_prog_size.cor";
    tmp->fd = open(filename, O_RDONLY);

    if (!tmp || !tmp->fd)
        return;
    cr_assert_eq(check_header(tmp, filename), -84);
    cr_assert_stderr_eq_str(
            "cor/incorrect_prog_size.cor : Wrong program size in the header\n");
    close(tmp->fd);
    free(tmp);
}
