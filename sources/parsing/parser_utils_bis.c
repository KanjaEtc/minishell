/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:40:55 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 21:28:58 by marotsen         ###   ########.fr       */
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

static t_token	*create_redir_pair(t_token *curr)
{
	t_token	*redir;

	redir = copy_token(curr);
	if (!redir)
		return (NULL);
	if (curr->next)
	{
		redir->next = copy_token(curr->next);
		if (!redir->next)
		{
			free(redir->value);
			free(redir);
			return (NULL);
		}
	}
	return (redir);
}

void	add_redir_node(t_token **redirs, t_token *curr)
{
	t_token	*node;
	t_token	*last;

	node = create_redir_pair(curr);
	if (!node)
		return ;
	if (!*redirs)
	{
		*redirs = node;
		return ;
	}
	last = *redirs;
	while (last->next)
		last = last->next;
	last->next = node;
}

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->args = NULL;
	cmds->redirs = NULL;
	cmds->next = NULL;
	return (cmds);
}

void	add_cmd_back(t_cmd **list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!list || !new_cmd)
		return ;
	if (*list == NULL)
	{
		*list = new_cmd;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
}
