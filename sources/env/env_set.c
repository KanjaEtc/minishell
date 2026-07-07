#include "../../includes/minishell.h"

t_env	*fill_env(char *env_str, t_env *env)
{
    char *sep;
    size_t key_len;

    sep = ft_strchr(env_str, '=');
    if (!sep)
    {
        free(env);
        return (NULL);
    }
    key_len = sep - env_str;
    env->key = malloc(key_len + 1);
    if (!env->key)
    {
        free(env);
        return (NULL);
    }
    ft_strlcpy(env->key, env_str, key_len + 1);
    env->value = ft_strdup(sep + 1);
    if (!env->value)
    {
        free(env->key);
        free(env);
        return (NULL);
    }
    return (env);
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
        if (!fill_env(envp[i], node))
            return (free_env(head), NULL);
        if (!head)
            head = node;
        else
            tail->next = node;
        tail = node;
        i++;
    }
    return (head);
}


void *free_env(t_env *env)
{
    t_env *current = env;
    while (current)
    {
        t_env *temp = current;
        current = current->next;
        if (temp->key)
            free(temp->key);
        if (temp->value)
            free(temp->value);
        free(temp);
    }
    return (NULL);
}
 
t_env *empty_env(void)
{
    t_env *pwd;
    t_env *shlvl;
    t_env *path;

    pwd = malloc(sizeof(t_env));
    shlvl = malloc(sizeof(t_env));
    path = malloc(sizeof(t_env));
    if (!pwd || !shlvl || !path)
        return (free(pwd), free(shlvl), free(path), NULL);
    pwd->key = ft_strdup("PWD");
    pwd->value = getcwd(NULL, 0);
    shlvl->key = ft_strdup("SHLVL");
    shlvl->value = ft_strdup("1");
    path->key = ft_strdup("PATH");
    path->value = ft_strdup("/usr/local/bin:/usr/bin:/bin");
    if (!pwd->key || !pwd->value || !shlvl->key || !shlvl->value || !path->key || !path->value)
        return (free_env(pwd), free_env(shlvl), free_env(path), NULL);
    pwd->next = shlvl;
    shlvl->next = path;
    path->next = NULL;
    return (pwd);
}

t_env *env_set(char **envp)
{
    if (envp && envp[0])
        return (init_env(envp));
    else
        return (empty_env());
}