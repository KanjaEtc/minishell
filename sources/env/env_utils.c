#include "../../includes/minishell.h"

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
	char	**envp;
	t_env	*current;
	char	*val;
	int		count;
	int		i;

	count = 0;
	current = env; 
	while (current) 
	{
		count++; 
		current = current->next; 
	}
	envp = malloc(sizeof(char *) * (count + 1)); 
	if (!envp)
		return (NULL); 
	current = env; 
	i = 0;
	while (i < count) 
	{
		if (current->value)
			val = current->value;
		else
			val = "";
		
		envp[i] = ft_strjoin_three(current->key, "=", val); 
		current = current->next; 
		i++; 
	}
	envp[count] = NULL; 
	return (envp); 
}
