/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:03:49 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 21:20:57 by marotsen         ###   ########.fr       */
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

static int	print_cmd_error(char *cmd, int has_perm)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (has_perm)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

int	find_executable_path(char *cmd, char **env_paths, char **path)
{
	int	ret;
	int	has_perm;

	has_perm = 0;
	*path = NULL;
	if (ft_strchr(cmd, '/'))
	{
		ret = check_direct_path(cmd);
		if (ret != 0)
			return (ret);
		*path = ft_strdup(cmd);
		if (!*path)
			return (126);
		return (0);
	}
	*path = search_in_paths(cmd, env_paths, &has_perm);
	if (*path)
		return (0);
	return (print_cmd_error(cmd, has_perm));
}
