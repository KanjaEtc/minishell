#include "../../includes/minishell.h"
static void	clean_cmd_args(t_cmd *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		tmp = cmd->args[i];
		cmd->args[i] = strip_quotes(tmp);
		free(tmp);
		i++;
	}
}

void	exec_simple_cmd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	envp = env_to_envp(env);
	clean_cmd_args(cmd);
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (execve(cmd->args[0], cmd->args, envp) == -1)
		{
			perror("minishell");
			exit(126);
		}
	}
	path = get_path(cmd->args[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		exit(127);
	}
	execve(path, cmd->args, envp);
	perror("minishell: execve failed");
	free(path);
	exit(1);
}