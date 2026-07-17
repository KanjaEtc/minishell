#include "../../includes/minishell.h"

void	expand_tokens(t_token **tokens, t_env *env)
{
	t_token *curr;
	t_token	*next;
	t_type prev_type;

	curr = *tokens;
	prev_type = WORD;
	while (curr)
	{
		next = curr->next;
		if (curr->type == WORD && curr->value)
		{
			if (ft_strchr(curr->value, '\'') || ft_strchr(curr->value, '"'))
				curr->was_quoted = 1;
			curr->value = expand_string(curr->value, env);
			if ((prev_type == RED_IN || prev_type == RED_OUT
					|| prev_type == APPEND) && !curr->was_quoted
				&& (curr->value[0] == '\0' || has_unquoted_space(curr->value)))
				curr->invalid_redir = 1;
		}
		prev_type = curr->type;
		if (curr->type == WORD && has_unquoted_space(curr->value)
			&& !curr->invalid_redir)
			insert_split_tokens(tokens, curr, split_expanded(curr->value));
		curr = next;
	}
}

char	*expand_string(char *str, t_env *env)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (str && str[i])
	{
		status = update_quote_status(str[i], status);
		if (str[i] == '$' && status != '\'')
		{
			if (str[i + 1] && (is_valid_var_char(str[i + 1]) || str[i + 1] == '?'))
				str = handle_dollar(str, &i, env);
			else
				i++;
		}
		else
			i++;
	}
	return (str);
}

static char	*build_new_string(char *str, char *val, int i, int len)
{
	char	*before;
	char	*after;
	char	*res;
	char	*tmp;

	before = ft_substr(str, 0, i);
	after = ft_strdup(str + i + len + 1);
	tmp = ft_strjoin(before, val);
	res = ft_strjoin(tmp, after);
	free(before);
	free(after);
	free(tmp);
	return (res);
}

char	*handle_dollar(char *str, int *i, t_env *env)
{
	char	*name;
	char	*val;
	char	*new_s;
	int		len;

	len = var_len(&str[*i + 1]);
	name = ft_substr(str, *i + 1, len);
	if (ft_strcmp(name, "?") == 0)
		val = ft_itoa(g_var);
	else
		val = ft_strdup(ft_get_env(name, env) ? ft_get_env(name, env) : "");
	new_s = build_new_string(str, val, *i, len);
	*i += ft_strlen(val); // On avance l'index à la fin de la valeur insérée
	if (ft_strcmp(name, "?") == 0)
		free(val);
	else
		free(val);
	free(name);
	free(str);
	return (new_s);
}