#include "minishell.h"

int	is_valid_var_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	var_len(char *str)
{
	int	i;

	if (str[0] == '?')
		return (1);
	i = 0;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	return (i);
}

char	*expand_string(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == "'")
		{
			while (str[i] != "'")
				i++;
		}
		
	}
}