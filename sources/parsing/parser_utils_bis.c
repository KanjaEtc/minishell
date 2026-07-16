#include "../../includes/minishell.h"

t_token	*copy_token(t_token *src)
{
	t_token	*dst;

	if (!src)
		return(NULL);
	dst = malloc(sizeof(t_token));
	if (!dst)
		return (NULL);
	dst->type = src->type;
	if (!src->value)
		dst->value = NULL;
	else
		dst->value = ft_strdup(src->value);
	dst->next = NULL;
	return (dst);
}

void	add_redir_node(t_token **redirs, t_token *curr)
{
	t_token	*redir;
	t_token	*file;
	t_token	*last;

	file = NULL;
	redir = copy_token(curr);
	if (curr->next)
		file = copy_token(curr->next);
	redir->next = file;
	if (!*redirs)
	{
		*redirs = redir;
		return;
	}
	last = *redirs;
	while (last->next)
		last = last->next;
	last->next = redir;
}
