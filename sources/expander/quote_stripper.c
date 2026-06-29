#include "../minishell.h"
#include "expand.h"

int	get_clean_len(char	*str)
{
	t_status	quote;
	int			i;
	int			len;

	i = 0;
	len = 0;
	quote.status = NO_QUOTES;
	while (str[i])
	{
		if (str[i] == '\'' && quote.status == NO_QUOTES)
			quote.status = IN_S_QUOTES;
		else if (str[i] == '"' && quote.status == NO_QUOTES)
			quote.status = IN_D_QUOTES;
		else if (str[i] == '\'' && quote.status == IN_S_QUOTES)
			quote.status = NO_QUOTES;
		else if (str[i] == '"' && quote.status == IN_D_QUOTES)
			quote.status = NO_QUOTES;
		else
			len++;
		i++;
	}
	return (len);
}


char	*strip_quotes(char *str)
{
	t_status	quote;
	char		*new_s;
	int			i;
	int			j;

	if (!str)
		return (NULL);
	new_s = malloc(sizeof(char) * (get_clean_len(str) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	quote.status = NO_QUOTES;
	while (str[i])
	{
		if (str[i] == '\'' && quote.status == NO_QUOTES)
			quote.status = IN_S_QUOTES;
		else if (str[i] == '"' && quote.status == NO_QUOTES)
			quote.status = IN_D_QUOTES;
		else if (str[i] == '\'' && quote.status == IN_S_QUOTES)
			quote.status = NO_QUOTES;
		else if (str[i] == '"' && quote.status == IN_D_QUOTES)
			quote.status = NO_QUOTES;
		else
			new_s[j++] = str[i];
		i++;
	}
	new_s[j] = '\0';
	return (new_s);
}
