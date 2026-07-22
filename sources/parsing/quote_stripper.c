/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stripper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:42:35 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:42:54 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_clean_len(char *str)
{
	int	i;
	int	len;
	int	status;

	i = 0;
	len = 0;
	status = 0;
	while (str[i])
	{
		if (status == 0 && (str[i] == '\'' || str[i] == '\"'))
			status = str[i];
		else if (status == str[i])
			status = 0;
		else
			len++;
		i++;
	}
	return (len);
}

char	*strip_quotes(char *str)
{
	char	*res;
	int		i[3];

	res = malloc(get_clean_len(str) + 1);
	if (!res)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (str[i[0]])
	{
		if (i[2] == 0 && (str[i[0]] == '\''
				|| str[i[0]] == '\"'))
			i[2] = str[i[0]];
		else if (i[2] == str[i[0]])
			i[2] = 0;
		else
			res[i[1]++] = str[i[0]];
		i[0]++;
	}
	res[i[1]] = '\0';
	return (res);
}

void	clean_all_tokens(t_token *tokens)
{
	t_token	*curr;
	char	*tmp;

	curr = tokens;
	while (curr)
	{
		if (curr->type == WORD && curr->value)
		{
			tmp = strip_quotes(curr->value);
			if (tmp)
			{
				free(curr->value);
				curr->value = tmp;
			}
		}
		curr = curr->next;
	}
}
