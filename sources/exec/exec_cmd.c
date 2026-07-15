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

int exec_builtin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (echo_builtin(cmd->argc, cmd->args));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd_builtin(env, cmd->args));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd_builtin(env));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		if (export_builtin(cmd->args[1], env) != NULL)
			return (0);
		return (1);
	}
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset_builtin(env, cmd->args));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env_builtin(env));
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
	    return (exit_builtin(cmd->args, env));
	return (0);
}
static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char *get_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = ft_get_env("PATH", env); 
	if (!path_env)
		return (NULL); 
	paths = ft_split(path_env, ':'); 
	if (!paths)
		return (NULL); 
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_three(paths[i], "/", cmd); 
		if (access(full_path, X_OK) == 0) 
		{
			free_split(paths); 
			return (full_path); 
		}
		free(full_path); 
		i++; 
	}
	free_split(paths);  
	return (NULL); 
}

void exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return;
	if (is_builtin(cmd->args[0]))
	{
		g_var = exec_builtin(cmd, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			exec_simple_cmd(cmd, env);
		else if (pid < 0)
			perror("fork");
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_var = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_var = 128 + WTERMSIG(status);
		}
	}
}
