/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:04:28 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 21:21:21 by marotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_directory_or_error(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": Is a directory", 2);
			return (126);
		}
	}
	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	return (0);
}

void	exec_simple_cmd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;
	char	**paths;
	int		ret;

	if (!cmd || !cmd->args || !cmd->args[0])
		clean_and_exit(0);
	envp = env_to_envp(env);
	paths = NULL;
	while (env && ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	if (env)
		paths = ft_split(env->value, ':');
	ret = find_executable_path(cmd->args[0], paths, &path);
	if (ret != 0)
		(free_split(paths), free_envp(envp), clean_and_exit(ret));
	execve(path, cmd->args, envp);
	perror("minishell");
	(free_split(paths), free(path), free_envp(envp), clean_and_exit(126));
}

static int	check_direct_path(char *cmd)
{
	int	ret;

	ret = check_directory_or_error(cmd);
	if (ret != 0)
		return (ret);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (0);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (127);
}

static char	*search_in_paths(char *cmd, char **env_paths, int *has_perm)
{
	int		i;
	char	*full_path;

	i = 0;
	while (env_paths && env_paths[i])
	{
		full_path = build_path(env_paths[i], cmd);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path);
			*has_perm = 1;
		}
		free(full_path);
		i++;
	}
	return (NULL);
}
