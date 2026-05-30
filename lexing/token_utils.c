#include "minishell.h"

t_token	*new_token(char *val, t_type type)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = val;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_token_back(t_token **list, t_token *new_token)
{
	t_token *last;

	if (!list || !new_token)
		return;
	if (*list == NULL)
	{
		*list = new_token;
		return;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_token;
}

void	free_token(t_token **list)
{
	t_token	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
}

int	ft_strcmp(const char *s1,const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}