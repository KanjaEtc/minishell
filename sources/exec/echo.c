#include "../../includes/minishell.h"

static int  is_n_option(char *arg)
{
    int i;

    if (!arg || arg[0] != '-' || arg[1] != 'n')
        return (0);
    i = 2;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int echo_builtin(int argc, char **argv)
{
    int i;
    int option;

    option = 0;
    i = 1;
    while (i < argc && is_n_option(argv[i]))
    {
        option = 1;
        i++;
    }
    while (i < argc)
    {
        ft_putstr_fd(argv[i], 1);
        if (i < argc - 1)
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!option)
        ft_putstr_fd("\n", 1);
    return (0);
}
