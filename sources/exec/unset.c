#include "../../includes/minishell.h"

int unset_builtin(t_env *env, char **keys)
{
    t_env *current;
    t_env *prev = NULL;

    current = env;
    while (current)
    {
        int i = 0;
        while (keys[i])
        {
            if (ft_strcmp(current->key, keys[i]) == 0)
            {
                if (prev)
                    prev->next = current->next;
                else
                    env = current->next;
                return (free(current->key), free(current->value), free(current), 0);
            }
            i++;
        }
        prev = current;
        current = current->next;
    }
    return (0);
}
