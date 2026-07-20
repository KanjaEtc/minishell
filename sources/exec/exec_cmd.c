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

// static void	free_split(char **split)
// {
// 	int	i;

// 	if (!split)
// 		return ;
// 	i = 0;
// 	while (split[i])
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// }

// char	*get_path(char *cmd, t_env *env)
// {
// 	char	*path_env;
// 	char	**paths;
// 	char	*full_path;
// 	int		i;

// 	path_env = ft_get_env("PATH", env);
// 	if (!path_env)
// 		return (NULL);
// 	paths = ft_split(path_env, ':');
// 	if (!paths)
// 		return (NULL);
// 	i = 0;
// 	while (paths[i])
// 	{
// 		full_path = ft_strjoin_three(paths[i], "/", cmd);
// 		if (access(full_path, X_OK) == 0)
// 		{
// 			free_split(paths);
// 			return (full_path);
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	free_split(paths);
// 	return (NULL);
// }

void	exec_single_builtin(t_cmd *cmd, t_env **env)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return ;
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