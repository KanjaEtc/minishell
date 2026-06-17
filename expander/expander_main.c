#include "expander.h"
#include "../env/env.h"

int main(int ac, char **av, char **envp)
{
    (void)ac; (void)av;
    if (!envp || envp[0] == NULL)
        return (1); 
    t_env *env = init_env(envp);
    print_env(env);
    free_env(env);
    return (0);
}
