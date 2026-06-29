#include "../../includes/minishell.h"

t_env	*create_new_t_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	ft_add_env_back(t_env **list, t_env *new_node)
{
	t_env	*last;

	if (!list || !new_node)
		return;
	if (*list == NULL)
	{
		*list = new_node;
		return;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

char	*ft_get_env(char *key, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char **env_to_envp(t_env *env)
{
    int count = 0;
    t_env *current = env;
    while (current)
    {
        count++;
        current = current->next;
    }

    char **envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL);

    current = env;
    for (int i = 0; i < count; i++)
    {
        envp[i] = ft_strjoin_three(current->key, "=", current->value);
        current = current->next;
    }
    envp[count] = NULL;

    return (envp);
}