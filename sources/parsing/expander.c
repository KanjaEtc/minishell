#include "../../includes/minishell.h"

void	expand_tokens(t_token *tokens, t_env *env)
{
	t_token	*current;
	char *stripped;

	current = tokens;
	while (current)
	{
		if (current->type == WORD && current->value)
		{
			current->value = expand_string(current->value, env);
			if (current->value)
			{
				stripped = strip_quotes(current->value);
				if (stripped)
				{
					free(current->value);
					current->value = stripped;
				}
			}
		}
		current = current->next;
	}
}

char	*expand_string(char *str, t_env *env)
{
	t_status	state;
	int			i;

	i = 0;
	state.status = NO_QUOTES;
	while (str[i])
	{
		if (str[i] == '\'' && state.status == NO_QUOTES)
			state.status = IN_S_QUOTES;
		else if (str[i] == '\'' && state.status == IN_S_QUOTES)
			state.status = NO_QUOTES;
		else if (str[i] == '\"' && state.status == NO_QUOTES)
			state.status = IN_D_QUOTES;
		else if (str[i] == '\"' && state.status == IN_D_QUOTES)
			state.status = NO_QUOTES;
		if (str[i] == '$' && state.status != IN_S_QUOTES)
		{
			if (str[i + 1] && (is_valid_var_char(str[i + 1]) || str[i + 1] == '?'))
			{
				str = handle_dollar(str, i, env);
				i = -1;
				state.status = NO_QUOTES;
			}
		}
		i++;
	}
	return (str);
}

char	*handle_dollar(char *str, int i, t_env *env)
{
	char	*var_name;
	char	*before;
	char	*after;
	char	*new_s;
	char	*var_value;
	int 	after_start;
	int 	len;

	len = var_len(&str[i + 1]);
	var_name = ft_substr(str, i + 1, len);
	before = ft_substr(str, 0, i);
	after_start = i + 1 + ft_strlen(var_name);
	after = ft_substr(str, after_start, ft_strlen(str) - after_start);
	if (ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(g_var);
	else
		var_value = ft_get_env(var_name, env);
	if (!var_value)
		var_value = "";
	new_s = ft_strjoin_three(before, var_value, after);
	if (ft_strcmp(var_name, "?") == 0 && var_value && *var_value)
		free(var_value);
	return (free(str), free(before), free(after), free(var_name), new_s);
}
