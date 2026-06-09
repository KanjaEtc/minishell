#include "minishell.h"

int	update_quote_status(char c, int curr_status)
{
	if (curr_status == 0 && (c == '\'' || c == '"'))
		return (c);
	else if (curr_status)
		return (0);
	return (curr_status);
}

int	unclosed_quote(char *line)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (line[i])
	{
		status = update_quote_status(line[i], status);
		i++;
	}

	if (status != 0)
		return (1); //ca veut dire qu'il reste une quote non fermee
	return (0);
}

int	ft_strcmp(const char *s1,const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	assign_token_types(t_token *token_list)
{
	t_token *current;

	current = token_list;
	while (current)
	{
		if (ft_strcmp(current->value, "|") == 0)
			current->type = PIPE;
		else if (ft_strcmp(current->value, "<") == 0)
			current->type = RED_IN;
		else if (ft_strcmp(current->value, ">") == 0)
			current->type = RED_OUT;
		else if (ft_strcmp(current->value, "<<") == 0)
			current->type = HEREDOC;
		else if (ft_strcmp(current->value, ">>") == 0)
			current->type = APPEND;
		current = current->next;
	}
}
