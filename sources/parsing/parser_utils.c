/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:27:08 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 17:05:59 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	free_redir_pair(t_token *curr)
{
	t_token	*file;

	if (!curr)
		return ;
	file = curr->next;
	if (curr->value)
		free(curr->value);
	free(curr);
	if (file)
	{
		if (file->value)
			free(file->value);
		free(file);
	}
}

static void	free_redirs(t_token **redirs)
{
	t_token	*curr;
	t_token	*file;

	if (!redirs || !*redirs)
		return ;
	while (*redirs)
	{
		curr = *redirs;
		file = curr->next;
		*redirs = file ? file->next : NULL;
		free_redir_pair(curr);
	}
}

void	free_cmd_table(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		if (cmd->redirs)
			free_redirs(&cmd->redirs);
		free(cmd);
		cmd = tmp;
	}
}

int	count_arg(t_token *tokens)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = tokens;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == WORD)
		{
			count++;
			curr = curr->next;
		}
		else
		{
			if (curr->next)
				curr = curr->next->next;
			else
				curr = curr->next;
		}
	}
	return (count);
}

char	**get_cmd_args(t_token *tokens)
{
	char	**args;
	int		i;

	if (!tokens)
		return (NULL);
	args = malloc(sizeof(char *) * (count_arg(tokens) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			args[i++] = ft_strdup(tokens->value);
		else if (tokens->next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
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
