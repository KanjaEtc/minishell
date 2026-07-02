#include "minishell.h"

test_cmd	*lst_new_cmd(void)
{
	test_cmd	*commands;

	commands = malloc(sizeof(test_cmd));
	if (!commands)
		return(NULL);
	commands->args = NULL;
	commands->redirs = NULL;
	commands->next = NULL;
	return (commands);
}

void	free_cmd_table(test_cmd *cmd)
{
	test_cmd	*tmp;
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
	t_token	*current;
	char	**args;
	int		i;

	if (!tokens)
		return (NULL);
	args = malloc(sizeof(char *) * (count_arg(tokens) + 1));
	if (!args)
		return (NULL);
	i = 0;
	current = tokens;
	while (current && current->type != PIPE)
	{
		if (current->type == WORD)
			args[i++] = ft_strdup(current->value);
		else if (current->type != PIPE && current->next)
				current = current->next;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

void	add_cmd_back(test_cmd **list, test_cmd *new_cmd)
{
	test_cmd	*last;

	if (!list || !new_cmd)
		return;
	if (*list == NULL)
	{
		*list = new_cmd;
		return;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
}
