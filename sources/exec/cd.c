#include "../../includes/minishell.h"

int cd_builtin(t_env *env, char **args)
{
    char *path;
    char *home;

    if (args[0] == NULL || ft_strcmp(args[0], "~") == 0)
    {
        home = ft_get_env("HOME", env);
        if (home == NULL)
        {
            write(2, "cd: HOME not set\n", 17);
            return (1);
        }
        path = home;
    }
    else
        path = args[0];

    if (chdir(path) != 0)
    {
        perror("cd");
        return (1);
    }
    return (0);
}