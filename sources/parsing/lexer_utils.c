/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:29:13 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:29:14 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_quote_status(char c, int curr_status)
{
	if (curr_status == 0 && (c == '\'' || c == '"'))
		return (c);
	else if (curr_status == c)
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
		return (1);
	return (0);
}

void	assign_token_types(t_token *token_list)
{
	t_token	*current;

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
