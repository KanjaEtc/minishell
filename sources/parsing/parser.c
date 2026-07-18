/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:40:06 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 21:34:14 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*parse_single_cmd(t_token **curr)
{
	t_cmd	*cmd;

	cmd = lst_new_cmd();
	if (!cmd)
		return (NULL);
	cmd->args = get_cmd_args(*curr);
	while (*curr && (*curr)->type != PIPE)
	{
		if ((*curr)->type == RED_IN || (*curr)->type == RED_OUT
			|| (*curr)->type == APPEND || (*curr)->type == HEREDOC)
		{
			add_redir_node(&cmd->redirs, *curr);
			if ((*curr)->next)
				*curr = (*curr)->next;
		}
		if (*curr)
			*curr = (*curr)->next;
	}
	return (cmd);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;

	cmd_list = NULL;
	while (tokens)
	{
		new_cmd = parse_single_cmd(&tokens);
		if (!new_cmd)
			return (NULL);
		add_cmd_back(&cmd_list, new_cmd);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (cmd_list);
}
