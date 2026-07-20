/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:03:49 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:03:49 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
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

void	exec_single_builtin(t_cmd *cmd, t_env **env)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		if (saved_stdin != -1)
			close(saved_stdin);
		if (saved_stdout != -1)
			close(saved_stdout);
		return ;
	}
	if (apply_redirections(cmd->redirs) != -1)
		g_var = exec_builtin(cmd, env);
	else
		g_var = 1;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	exec_builtin(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (echo_builtin(cmd->args));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd_builtin(*env, cmd->args));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd_builtin(*env));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (dispatch_export(cmd, env));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset_builtin(env, cmd->args));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env_builtin(*env));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (exit_builtin(cmd->args, env));
	return (0);
}