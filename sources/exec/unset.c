#include "../../includes/minishell.h"

int unset_builtin(t_env **env, char *key)
{
    t_env *current = *env;
    t_env *prev = NULL;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return (0);
        }
        prev = current;
        current = current->next;
    }
    return (0);
}