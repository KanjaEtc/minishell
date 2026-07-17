#include "../../includes/minishell.h"

static char	*read_heredoc_line(void)
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

static char	*write_heredoc_to_temp(char *limiter, int count)
{
	char	*filename;
	char	*count_str;
	char	*line;
	int		fd;

	count_str = ft_itoa(count);
	filename = ft_strjoin("/tmp/.minishell_hd_", count_str);
	free(count_str);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (free(filename), NULL);
	while (1)
	{
		line = read_heredoc_line(); /* L'appel corrigé est ici ! */
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (filename);
}

void	exec_all_heredocs(t_cmd *cmds)
{
	t_cmd		*curr_cmd;
	t_token		*curr_redir;
	char		*temp_file;
	static int	hd_counter = 0;

	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redirs;
		while (curr_redir)
		{
			if (curr_redir->type == HEREDOC)
			{
				temp_file = write_heredoc_to_temp(curr_redir->value, hd_counter++);
				if (temp_file)
				{
					free(curr_redir->value);
					curr_redir->value = temp_file;
					curr_redir->type = RED_IN;
				}
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
}

void	unlink_temporary_heredocs(t_cmd *cmds)
{
	t_cmd	*curr_cmd = cmds;
	t_token	*curr_redir;

	while (curr_cmd)
	{
		curr_redir = curr_cmd->redirs;
		while (curr_redir)
		{
			if (curr_redir->type == RED_IN && 
					ft_strncmp(curr_redir->value, "/tmp/.minishell_hd_", 19) == 0)
			{
				unlink(curr_redir->value);
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
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
			break;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}