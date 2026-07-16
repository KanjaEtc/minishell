#include "../../includes/minishell.h"

static void	free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static void	delete_env_node(t_env *env, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env = current->next;
			free_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_builtin(t_env *env, char **keys)
{
	int	i;

	if (!keys || !env)
		return (0);
	i = 1;
	while (keys[i])
	{
		delete_env_node(env, keys[i]);
		i++;
	}
	return (0);
}
