/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:43:14 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:43:15 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redir_syntax(t_token *curr)
{
	if (curr->type == RED_IN || curr->type == RED_OUT
		|| curr->type == APPEND || curr->type == HEREDOC)
	{
		if (!curr->next)
		{
			ft_putstr_fd("minishell: syntax error near `newline'\n", 2);
			return (g_var = 2, 1);
		}
		if (curr->next->type != WORD)
		{
			ft_putstr_fd("minishell: syntax error near `", 2);
			ft_putstr_fd(curr->next->value, 2);
			ft_putstr_fd("'\n", 2);
			return (g_var = 2, 1);
		}
	}
	return (0);
}

static int	check_pipe_syntax(t_token *curr)
{
	if (curr->type == PIPE)
	{
		if (!curr->next)
		{
			ft_putstr_fd("minishell: syntax error near`|'\n", 2);
			return (g_var = 2, 1);
		}
		if (curr->next->type == PIPE)
		{
			ft_putstr_fd("minishell: syntax error near 1|'\n", 2);
			return (g_var = 2, 1);
		}
	}
	return (0);
}

int	check_syntax_errors(t_token *tokens)
{
	t_token	*curr;

	if (!tokens)
		return (0);
	if (tokens->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near `|'\n", 2);
		return (g_var = 2, 1);
	}
	curr = tokens;
	while (curr)
	{
		if (check_redir_syntax(curr) || check_pipe_syntax(curr))
			return (1);
		curr = curr->next;
	}
	return (0);
}
