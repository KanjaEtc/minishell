/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:28:43 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:29:59 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	handle_lexer_operators(char *line, int *i,
	int *start, t_token **token_list)
{
	char	*curr_word;

	if (*i > *start)
	{
		curr_word = ft_substr(line, *start, *i - *start);
		add_token_back(token_list, new_token(curr_word, WORD));
	}
	if ((line[*i] == '<' && line[*i + 1] == '<')
		|| (line[*i] == '>' && line[*i + 1] == '>'))
	{
		curr_word = ft_substr(line, *i, 2);
		add_token_back(token_list, new_token(curr_word, WORD));
		(*i)++;
	}
	else
	{
		curr_word = ft_substr(line, *i, 1);
		add_token_back(token_list, new_token(curr_word, WORD));
	}
	*start = *i + 1;
}

static void	process_char(char *line, int *i, int *start, t_token **token_list)
{
	char	*curr;

	if (line[*i] == ' ' || line[*i] == '\t')
	{
		if (*i > *start)
		{
			curr = ft_substr(line, *start, *i - *start);
			add_token_back(token_list, new_token(curr, WORD));
		}
		while (line[*i] == ' ' || line[*i] == '\t')
			(*i)++;
		*start = *i;
		(*i)--;
	}
	else if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
		handle_lexer_operators(line, i, start, token_list);
}

t_token	*lexer(char *line)
{
	t_token	*token_list;
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
			process_char(line, &i, &start, &token_list);
		i++;
	}
	if (line[start] != '\0')
		add_token_back(&token_list,
			new_token(ft_substr(line, start, i - start), WORD));
	assign_token_types(token_list);
	return (token_list);
}

t_token	*new_token(char *val, t_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = val;
	new->type = type;
	new->was_quoted = 0;
	new->invalid_redir = 0;
	new->next = NULL;
	return (new);
}

void	add_token_back(t_token **list, t_token *new_token)
{
	t_token	*last;

	if (!list || !new_token)
		return ;
	if (*list == NULL)
	{
		*list = new_token;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_token;
}
