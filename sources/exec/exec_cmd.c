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

void exec_builtin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		echo_builtin(cmd->argc, cmd->args);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		cd_builtin(env, cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		pwd_builtin(env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		export_builtin(cmd->args[1], env);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		unset_builtin(env, cmd->args);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		env_builtin(env);
	// else if (ft_strcmp(cmd->cmd, "exit") == 0)
	//     exit_builtin(cmd->args);
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

void exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])\
		return;
	if (is_builtin(cmd->args[0]))
		exec_builtin(cmd, env);
	else
	{
		pid = fork();
		if (pid == 0)
			exec_simple_cmd(cmd, env);
		else if (pid < 0)
			perror("fork");
		else
			waitpid(pid, NULL, 0);
	}
		
}