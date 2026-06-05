#include "minishell.h"

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

t_env	*init_env(char **envp)
{

	t_env	*env_list;
	t_env	*new_node;
	char	*tmp_key;
	char	*tmp_value;
	char	*sep;
	int		i;

	if (!envp || envp[0] == NULL)
		return (NULL); // il faut appeler une focntion qui va creer un environnement par defaut avec ls commands de base (pwd etc)
	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		sep = ft_strchr(envp[i], '=');
		if (sep)
		{
			tmp_key = ft_substr(envp[i], 0,sep - envp[i]);
			tmp_value = ft_substr(envp[i], (sep - envp[i]) + 1, ft_strlen(sep + 1));
			new_node = create_new_t_env(tmp_key, tmp_value);
			ft_add_env_back(&env_list, new_node);
			free(tmp_key);
			free(tmp_value);
		}
		i++;
	}
	return (env_list);
}