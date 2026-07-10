#include "minishell.h"

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;
	t_token	*curr;

	if (!tokens)
		return (NULL);
	cmd_list = NULL;
	curr = tokens;
	while (curr)
	{
		new_cmd = lst_new_cmd();
		if (!new_cmd)
			return (NULL);
		new_cmd->args = get_cmd_args(curr);
		while (curr && curr->type != PIPE)
		{
			if (curr->type == RED_IN || curr->type == RED_OUT 
				|| curr->type == APPEND || curr->type == HEREDOC)
			{
				add_redir_node(&new_cmd->redirs, curr);
				if (curr->next)
					curr = curr->next;
			}
			curr = curr->next;
		}
		add_cmd_back(&cmd_list, new_cmd);
		if (curr && curr->type == PIPE)
			curr = curr->next;
	}
	return (cmd_list);
}