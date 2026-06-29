#include "../../includes/minishell.h"

t_env	*fill_env(char *env_str, t_env *env)
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
            return (free(env->key), free(env), NULL);
        return (env);
    }
    else
        return (free(env->key), free(env), NULL);
}

t_env	*init_env(char **envp)
{
    t_env	*head;
    t_env	*tail;
    t_env	*node;
    int		i;

    head = NULL;
    tail = NULL;
    i = 0;
    while (envp[i])
    {
        node = malloc(sizeof(t_env));
        if (!node)
            return (free_env(head), NULL);
        node->next = NULL;
        fill_env(envp[i], node);
        if (!head)
            head = node;
        else
            tail->next = node;
        tail = node;
        i++;
    }
    return (head);
}

void print_env(t_env *env)
{
    t_env *current = env;
    while (current)
    {
        printf("%s = %s\n", current->key, current->value);
        current = current->next;
    }
}

void *free_env(t_env *env)
{
    t_env *current = env;
    while (current)
    {
        t_env *temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    return (NULL);
}
 