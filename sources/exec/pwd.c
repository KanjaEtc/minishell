#include "../../includes/minishell.h"

int pwd_builtin(t_env *env)
{
    char *pwd = ft_get_env("PWD", env);
    if (pwd)
    {
        ft_putstr_fd(pwd, 1);
        ft_putstr_fd("\n", 1);
        return (0);
    }
    else
    {
        ft_putstr_fd("pwd: PWD not set\n", 2);
        return (1);
    }
}