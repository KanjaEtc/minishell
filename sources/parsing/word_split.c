/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:45:46 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 21:37:48 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	extract_word(char *str, int *i, int *start,
	t_token **head)
{
	if (*i > *start)
		add_token_back(head, new_token(ft_substr(str, *start,
					*i - *start), WORD));
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	*start = *i;
}

t_token	*split_expanded(char *str)
{
	t_token	*head;
	int		i;
	int		start;
	int		st;

	head = NULL;
	i = 0;
	start = 0;
	st = 0;
	while (str[i])
	{
		st = update_quote_status(str[i], st);
		if (st == 0 && (str[i] == ' ' || str[i] == '\t'))
			extract_word(str, &i, &start, &head);
		else
			i++;
	}
	if (i > start)
		add_token_back(&head, new_token(ft_substr(str, start,
					i - start), WORD));
	return (head);
}

void	insert_split_tokens(t_token **head, t_token *curr,
	t_token *sub)
{
	t_token	*prev;
	t_token	*sub_last;

	sub_last = sub;
	while (sub_last && sub_last->next)
		sub_last = sub_last->next;
	if (sub_last)
		sub_last->next = curr->next;
	else
		sub = curr->next;
	prev = *head;
	if (prev == curr)
		*head = sub;
	else
	{
		while (prev && prev->next != curr)
			prev = prev->next;
		if (prev)
			prev->next = sub;
	}
	free(curr->value);
	free(curr);
}

int	has_unquoted_space(char *str)
{
	int	i;
	int	st;

	i = 0;
	st = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		st = update_quote_status(str[i], st);
		if (st == 0 && (str[i] == ' ' || str[i] == '\t'))
			return (1);
		i++;
	}
	return (0);
}
