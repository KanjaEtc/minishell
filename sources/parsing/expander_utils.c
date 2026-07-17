#include "../../includes/minishell.h"

int is_valid_var_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int var_len(char *str)
{
	int i;

	if (!str || !*str)
		return (0);
	if (str[0] == '?')
		return (1);
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	i = 0;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	return (i);
}

void	clean_empty_tokens(t_token **tokens)
{
	t_token	**curr;
	t_token	*tmp;

	curr = tokens;
	while (*curr)
	{
		if ((*curr)->value[0] == '\0' 
			&& !(*curr)->was_quoted && !(*curr)->invalid_redir)
		{
			tmp = *curr;
			*curr = (*curr)->next;
			free(tmp->value);
			free(tmp);
		}
		else
			curr = &(*curr)->next;
	}
}