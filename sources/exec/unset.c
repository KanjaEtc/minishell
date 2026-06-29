#include "../../includes/minishell.h"

int unset_builtin(t_env **env, char **keys)
{
    t_env *current = *env;
    t_env *prev = NULL;

    while (current)
    {
        char *key = current->key;
        int i = 0;
        while (keys[i])
        {
            if (ft_strcmp(current->key, keys[i]) == 0)
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
            i++;
        }
        prev = current;
        current = current->next;
    }
    return (0);
}
