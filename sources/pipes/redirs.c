#include "../../includes/minishell.h"

static int	open_redir_file(char *filename, t_type type)
{
	int	fd;

	fd = -1;
	if (type == RED_IN)
		fd = open(filename, O_RDONLY);
	else if (type == RED_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	apply_redirections(t_token *redirs)
{
	t_token	*curr;
	int		fd;

	curr = redirs;
	while (curr)
	{
		if (curr->next)
		{
			if (curr->type == HEREDOC)
				fd = handle_heredoc(curr->next->value);
			else
				fd = open_redir_file(curr->next->value, curr->type);
			if (fd == -1)
				return (perror("minishell: redirection failed"), -1);
			if (curr->type == RED_IN || curr->type == HEREDOC)
				dup2(fd, STDIN_FILENO);
			else if (curr->type == RED_OUT || curr->type == APPEND)
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (curr->next)
			curr = curr->next->next;
		else
			curr = curr->next;
	}
	return (0);
}