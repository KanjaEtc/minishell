#include "../../includes/minishell.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
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

static void	handle_parent_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		g_var = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_var = 128 + WTERMSIG(status);
}

void	exec_single_builtin(t_cmd *cmd, t_env **env)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return ;
	if (apply_redirections(cmd->redirs) != -1)
	{
		/* Remplace 'execute_builtin' par le nom de ta vraie fonction */
		g_var = exec_builtin(cmd, env);
	}
	else
		g_var = 1;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
		exec_single_builtin(cmd, &env);
	else
	{
		setup_child_signals();
		pid = fork();
		if (pid == 0)
		{
			if (apply_redirections(cmd->redirs) == -1)
				exit(1);
			exec_simple_cmd(cmd, env);
		}
		else if (pid < 0)
			perror("fork");
		else
			handle_parent_wait(pid);
	}
}

char	*build_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}
