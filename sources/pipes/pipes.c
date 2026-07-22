/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:20:13 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 21:38:54 by marotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process(t_cmd *cmd, int *pipe_fd, int prev_fd, t_env *env)
{
	setup_child_signals();
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (apply_redirections(cmd->redirs) == -1)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		g_var = exec_builtin(cmd, &env);
		exit(g_var);
	}
	exec_simple_cmd(cmd, env);
}

static int	parent_close_fds(int prev_fd, int *pipe_fd, t_cmd *curr)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (curr->next)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	else
		return (-1);
}

static void	wait_pipeline(pid_t last_pid)
{
	int	status;

	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			g_var = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_var = 128 + WTERMSIG(status);
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	setup_signals();
}

void	execute_pipeline(t_cmd *cmd_list, t_env **env)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;

	prev_fd = -1;
	last_pid = -1;
	setup_exec_signals();
	while (cmd_list)
	{
		if (cmd_list->next && pipe(pipe_fd) == -1)
			return (perror("minishell: pipe failed"));
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork failed"));
		if (pid == 0)
			child_process(cmd_list, pipe_fd, prev_fd, *env);
		prev_fd = parent_close_fds(prev_fd, pipe_fd, cmd_list);
		if (!cmd_list->next)
			last_pid = pid;
		cmd_list = cmd_list->next;
	}
	wait_pipeline(last_pid);
}

int	handle_heredoc(char *limiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	while (1)
	{
		line = read_heredoc_line();
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
