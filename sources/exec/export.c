#include "../../includes/minishell.h"

int	export_no_args(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (curr->value)
			printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
		else
			printf("declare -x %s\n", curr->key);
		curr = curr->next;
	}
	return (0);
}
static void	set_env_val(t_env *node, char *val)
{
	if (node->value)
		free(node->value);
	if (val)
		node->value = ft_strdup(val);
	else
		node->value = NULL;
}

t_env	*new_env_var(char *arg, t_env **env_list)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	export_builtin(arg, new);
	new->next = NULL;
    ft_add_env_back(env_list, new);
	return (new);
}

int	export_builtin(char *env_str, t_env *env)
{
    char *sep;
    char *key;
    char *value;
    t_env *current;

    sep = ft_strchr(env_str, '=');
    if (sep)
        key = ft_substr(env_str, 0, sep - env_str);
    else
        key = ft_strdup(env_str);
    value = NULL;
    if (sep)
        value = ft_strdup(sep + 1);
    current = env;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            set_env_val(current, value);
            return (free(key), free(value), 0);
        }
        current = current->next;
    }
    return (free(key), free(value), 1);
}