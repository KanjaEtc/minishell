#include "../../includes/minishell.h"

static void	extract_word(char *str, int *i, int *start, t_token **head)
{
	if (*i > *start)
		add_token_back(head, new_token(ft_substr(str, *start, *i - *start), WORD));
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	*start = *i;
}

t_token	*split_expanded(char *str)
{
	t_token *head;
	int     i;
	int     start;
	int     st;

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
		add_token_back(&head, new_token(ft_substr(str, start, i - start), WORD));
	return (head);
}

void	insert_split_tokens(t_token **head, t_token *curr, t_token *sub)
{
	t_token	*prev = *head;
	t_token	*sub_last = sub;
	t_token	*node;

	prev = *head;
	sub_last = sub;
	if (sub)
	{
		node = sub;
		while (sub_last->next)
			sub_last = sub_last->next;
	}
	else
		node = curr->next;
	if (prev == curr)
		*head = node;
	else
	{
		while (prev && prev->next != curr)
			prev = prev->next;
		if (prev)
			prev->next = node;
	}
	if (sub && sub_last)
		sub_last->next = curr->next;
	free(curr->value);
	free(curr);
}

int	has_unquoted_space(char *str)
{
	int i;
	int st;

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
