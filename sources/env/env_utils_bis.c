#include "../../includes/minishell.h"

int	is_valid_identifier(char *str, int is_unset)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while(str[i])
	{
		if (is_unset && str[i] == '=')
			return (0);
		if (str[i] == '=')
			break;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}