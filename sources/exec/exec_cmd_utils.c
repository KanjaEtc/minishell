/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:04:28 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:04:29 by ranoumba         ###   ########.fr       */
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

static void	free_envp(char **envp)
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
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			paths = ft_split(env->value, ':');
		env = env->next;
	}
	ret = find_executable_path(cmd->args[0], paths, &path);
	if (ret != 0)
	{
		free_split(paths);
		free_envp(envp);
		clean_and_exit(ret);
	}
	execve(path, cmd->args, envp);
	perror("minishell");
	free_split(paths);
	free(path);
	free_envp(envp);
	clean_and_exit(126);
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

int	find_executable_path(char *cmd, char **env_paths, char **path)
{
	int		ret;
	int		has_perm;

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
