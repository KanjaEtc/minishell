/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:40:55 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:40:56 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*copy_token(t_token *src)
{
	t_token	*dst;

	if (!src)
		return (NULL);
	dst = malloc(sizeof(t_token));
	if (!dst)
		return (NULL);
	dst->type = src->type;
	dst->was_quoted = src->was_quoted;
	dst->invalid_redir = src->invalid_redir;
	if (!src->value)
		dst->value = NULL;
	else
		dst->value = ft_strdup(src->value);
	dst->next = NULL;
	return (dst);
}

void	add_redir_node(t_token **redirs, t_token *curr)
{
	t_token	*redir;
	t_token	*file;
	t_token	*last;

	file = NULL;
	redir = copy_token(curr);
	if (!redir)
		return ;
	if (curr->next)
	{
		file = copy_token(curr->next);
		if (!file)
		{
			free(redir->value);
			free(redir);
			return ;
		}
	}
	redir->next = file;
	if (!*redirs)
	{
		*redirs = redir;
		return ;
	}
	last = *redirs;
	while (last->next && last->next->next)
		last = last->next->next;
	if (last->next)
		last->next->next = redir;
	else
		last->next = redir;
}
