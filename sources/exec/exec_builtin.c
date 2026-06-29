void exec_builtin(t_cmd *cmd, t_env **env)
{
    if (ft_strcmp(cmd->args[0], "echo") == 0)
        echo_builtin(cmd->args);
    else if (ft_strcmp(cmd->args[0], "cd") == 0)
        cd_builtin(cmd->args, env);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        pwd_builtin();
    else if (ft_strcmp(cmd->args[0], "export") == 0)
        export_builtin(cmd->args, env);
    else if (ft_strcmp(cmd->args[0], "unset") == 0)
        unset_builtin(env, cmd->args);
    else if (ft_strcmp(cmd->args[0], "env") == 0)
        env_builtin(*env);
    else if (ft_strcmp(cmd->args[0], "exit") == 0)
        exit_builtin(cmd->args);
}