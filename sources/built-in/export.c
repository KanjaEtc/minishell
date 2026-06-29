#include "env.h"

t_env	*new_env_var(char *arg, t_env **env_list)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	fill_export_env(arg, new);
	new->next = NULL;
    ft_add_env_back(env_list, new);
	return (new);
}

t_env	*fill_export_env(char *env_str, t_env *env)
{
    char *sep;
    size_t key_len;

    sep = ft_strchr(env_str, '=');
    if (sep)
    {
        key_len = sep - env_str;
        env->key = malloc(key_len + 1);
        if (!env->key)
            return (NULL);
        ft_strlcpy(env->key, env_str, key_len + 1);
        env->value = ft_strdup(sep + 1);
        if (!env->value)
         return (env);
    }
    else
    {
        env->key = ft_strdup(env_str);
        env->value = NULL;
    }
    return (env);
}