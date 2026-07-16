#include "../../includes/minishell.h"

static void	check_directory_or_error(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": Is a directory", 2);
			exit(126);
		}
	}
	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
}

void	exec_simple_cmd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	envp = env_to_envp(env);
	if (ft_strchr(cmd->args[0], '/'))
	{
		check_directory_or_error(cmd->args[0]);
		if (execve(cmd->args[0], cmd->args, envp) == -1)
		{
			perror("minishell");
			exit(126);
		}
	}
	path = get_path(cmd->args[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(path, cmd->args, envp);
	exit(127);
}
