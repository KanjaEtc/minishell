#include "../../includes/minishell.h"

void exit_builtin(int argc, char **args)
{
    int exit_code = 0; // Default exit code
    
    if (!args[0])
    {
        exit_code = g_var;
        exit(exit_code);
    }


    if (args[1] != NULL)
    {
        write(2, "exit: too many arguments\n", 25);
        g_var = 1; // Set exit status to 1 for error
        return;
    }
    {
        exit_code = ft_atoi(args[1]);
    }
    g_var = exit_code;
    exit(exit_code);
}