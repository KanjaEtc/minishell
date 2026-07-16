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