#include "minishell.h"

static void	handle_lexer_operators(char *line, int *i, int *start, t_token **token_list)
{
	char	*curr_word;
	
	if (*i > *start)
	{
		curr_word = ft_substr(line, *start, *i - *start);
		add_token_back(token_list, ft_token_new(curr_word, WORD));
	}
	if ((line[*i] == '<' && line[*i + 1] == '<') || (line[*i] == '>' && line[*i + 1] == '>'))
	{
		curr_word = ft_substr(line, *i, 2);
		add_token_back(token_list, ft_token_new(curr_word, WORD));
		(*i)++;
	}
	else
	{
		curr_word = ft_substr(line, *i, 1);
		add_token_back(token_list, ft_token_new(curr_word, WORD));
	}
	*start = *i + 1;
}

t_token	*lexer(char *line)
{
	t_token	*token_list;
	char	*curr_word;
	int		status;
	int		start;
	int		i;

	i = 0;
	start = 0;
	status = 0;
	token_list = NULL;
	while (line[i])
	{
		status = update_quote_status(line[i], status);
		if (status == 0)
		{
			if (line[i] == ' ' || line[i] == '\t')
			{
				if (i > start)
				{
					curr_word = ft_substr(line, start, i - start);
					add_token_back(&token_list,ft_token_new(curr_word, WORD));
				}
				start = i + 1;
			}
			else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
				handle_lexer_operators(line, &i, &start, &token_list);
		}
		i++;
	}
	if (line[start] != '\0')
	{
		curr_word = ft_substr(line, start, i - start);
		add_token_back(&token_list, ft_token_new(curr_word, WORD));
	}
	return (token_list);
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