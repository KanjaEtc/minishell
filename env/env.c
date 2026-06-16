#include "env.h"
#include "libft.h"

t_env	*init_env(char **envp)
{
    t_env	*env_struct;
    int		i;

    env_struct = NULL;
    i = 0;
    while (envp[i])
    {
        t_env	*node = malloc(sizeof(t_env));
        if (!node)
            return (NULL);
        char *sep = ft_strchr(envp[i], '=');
        // printf("i: %d, sep: %s\n", i, sep);
        if (sep)
        {
            size_t key_len = sep - envp[i];
            node->key = malloc(key_len + 1);
            if (!node->key)
                return (NULL);
            ft_strlcpy(node->key, envp[i], key_len + 1);
            node->value = ft_strdup(sep + 1);
            if (!node->value)
            {
                free(node->key);
                free(node);
                return (NULL);
            }
        }
        // else
        // {
        //     free(node);
        //     return (NULL);
        // }

        node->next = env_struct;   
        env_struct = node;
        i++;
    }
    return (env_struct);
}

void print_env(t_env *env)
{
    t_env *current = env;
    while (current)
    {
        printf("%s=\n%s\n", current->key, current->value);
        current = current->next;
    }
}

int main(int ac, char **av, char **envp)
{
    (void)ac; (void)av;
    printf("envp:\n");
    t_env *env = init_env(envp);
    printf("init ok:\n");
    print_env(env);
    return (0);
}