#include "../../includes/minishell.h"

int is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0)
        return (1);
    else if (ft_strcmp(cmd, "cd") == 0)
        return (1);
    else if (ft_strcmp(cmd, "pwd") == 0)
        return (1);
    else if (ft_strcmp(cmd, "export") == 0)
        return (1);
    else if (ft_strcmp(cmd, "unset") == 0)
        return (1);
    else if (ft_strcmp(cmd, "env") == 0)
        return (1);
    else if (ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}

void exec_builtin(t_cmd *cmd, t_env **env)
{
    if (ft_strcmp(cmd->cmd, "echo") == 0)
        echo_builtin(cmd->args);
    else if (ft_strcmp(cmd->cmd, "cd") == 0)
        cd_builtin(cmd->args, env);
    else if (ft_strcmp(cmd->cmd, "pwd") == 0)
        pwd_builtin();
    else if (ft_strcmp(cmd->cmd, "export") == 0)
        export_builtin(cmd->args, env);
    else if (ft_strcmp(cmd->cmd, "unset") == 0)
        unset_builtin(env, cmd->args);
    else if (ft_strcmp(cmd->cmd, "env") == 0)
        env_builtin(*env);
    else if (ft_strcmp(cmd->cmd, "exit") == 0)
        exit_builtin(cmd->args);
}
char *get_path(char *cmd, t_env *env)
{
    char *path_env;
    char **paths;

    path_env = ft_get_env("PATH", env);
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);

    char *full_path = NULL;
    int i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin_three(paths[i], "/", cmd);
        if (access(full_path, X_OK) == 0)
        {
            int j = 0;
            while (paths[j])
                free(paths[j++]);
            free(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }

    int j = 0;
    while (paths[j])
        free(paths[j++]);
    free(paths);
    return (NULL);
}

int exec_execve(t_cmd *cmd, t_env *env)
{
    char **envp = env_to_envp(env);
    if (!envp)
        return (-1);
    if (execve(cmd->cmd, cmd->args, envp) == -1)
    {
        perror("command not found : %s\n", cmd->cmd);
        return (-1);
    }
    return (0);
}

void exec_cmd(t_cmd *cmd, t_env **env)
{
    if (is_builtin(cmd->cmd))
        exec_builtin(cmd, env);
    else
        exec_execve(cmd, *env);
}