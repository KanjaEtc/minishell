#include "../includes/minishell.h"

void	clean_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->line)
		free(shell->line);
	if (shell->tokens)
		free_token(&shell->tokens);
	if (shell->cmds)
		free_cmd_table(shell->cmds);
	if (shell->env)
		free_env(shell->env);
	free(shell);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_split(char **split)
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

void	clean_and_exit(int status)
{
	t_shell	*shell;

	shell = get_shell(NULL);
	close_extra_fds();
	clean_shell(shell);
	rl_clear_history();
	exit(status);
}
