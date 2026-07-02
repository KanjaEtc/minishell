#include "minishell.h"

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*commands;

	commands = malloc(sizeof(t_cmd));
	if (!commands)
		return(NULL);
	commands->args = NULL;
	commands->redirs = NULL;
	commands->next = NULL;
	return (commands);
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
		free(cmd);
		cmd = tmp;
	}
}

int	count_arg(t_token *tokens)
{
@@ -22,7 +58,34 @@ int	count_arg(t_token *tokens)
			count++;
			curr = curr->next;
		}
		curr = curr->next;
		else
			curr = curr->next;
	}
	return (count);
}
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
