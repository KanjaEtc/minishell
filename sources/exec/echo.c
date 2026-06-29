#include "../../includes/minishell.h"
int echo_builtin(int argc, char **argv, int option)
{
    int i;
    
    i = 1;
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

int main (int argc, char **argv)
{
    int option;

    option = 0;
    if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
    {
        option = 1;
        argv++;
        argc--;
    }
    return (echo_builtin(argc, argv, option));
}