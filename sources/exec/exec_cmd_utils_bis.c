/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:59:16 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 21:21:48 by marotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	exec_cmd(t_cmd *cmd, t_env **env)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
		exec_single_builtin(cmd, env);
	else
	{
		setup_child_signals();
		pid = fork();
		if (pid == 0)
		{
			if (apply_redirections(cmd->redirs) == -1)
				exit(1);
			exec_simple_cmd(cmd, *env);
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
