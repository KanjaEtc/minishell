#include "../../includes/minishell.h"

int	handle_heredoc(char *limiter)
{
	char	*line;
	int		pipe_fd[2];
	
	if (pipe(pipe_fd) == 1)
		return (-1);
	while (1)
	{
		line = readline("> ");
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