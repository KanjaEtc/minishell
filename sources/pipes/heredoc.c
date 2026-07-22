/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:17:22 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 21:38:45 by marotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_heredoc_line(void)
{
	char	buf[2];
	char	*line;
	char	*temp;
	int		bytes;

	if (isatty(STDIN_FILENO))
		return (readline("> "));
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		bytes = read(STDIN_FILENO, buf, 1);
		if (bytes <= 0)
			break ;
		buf[1] = '\0';
		if (buf[0] == '\n')
			break ;
		temp = ft_strjoin_three(line, buf, "");
		free(line);
		line = temp;
	}
	if (bytes <= 0 && ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

static void	child_heredoc_loop(char *limiter, int fd, char *filename)
{
	char	*line;

	signal(SIGINT, handle_sigint_heredoc);
	free(filename);
	while (1)
	{
		line = read_heredoc_line();
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	clean_and_exit(0);
}

static char	*get_hd_filename(int count)
{
	char	*count_str;
	char	*filename;

	count_str = ft_itoa(count);
	if (!count_str)
		return (NULL);
	filename = ft_strjoin("/tmp/.minishell_hd_", count_str);
	free(count_str);
	return (filename);
}

static char	*write_heredoc_to_temp(char *limiter, int count)
{
	char	*filename;
	int		fd;
	int		status;
	pid_t	pid;

	filename = get_hd_filename(count);
	if (!filename)
		return (NULL);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (free(filename), NULL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_heredoc_loop(limiter, fd, filename);
	close(fd);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (g_var = 130, unlink(filename), free(filename), NULL);
	return (filename);
}

int	exec_all_heredocs(t_cmd *cmds)
{
	t_token		*redir;
	char		*temp;
	static int	hd_counter = 0;

	while (cmds)
	{
		redir = cmds->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC && redir->next)
			{
				temp = write_heredoc_to_temp(redir->next->value, hd_counter++);
				if (!temp && g_var == 130)
					return (setup_signals(), write(1, "\n", 1), -1);
				if (temp)
					(free(redir->next->value), redir->next->value = temp,
						redir->type = RED_IN);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (setup_signals(), 0);
}
