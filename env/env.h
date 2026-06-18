#ifndef ENV_H
# define ENV_H

#include <stdlib.h>
#include <stdio.h>
#include "../libft_stripped/libft_stripped.h"

typedef struct s_env
{
    char			*key;
    char			*value;
    struct s_env	*next;
}	t_env;

// Env functions
t_env	*fill_env(char *env_str, t_env *env);
t_env	*init_env(char **envp);
void	print_env(t_env *env);
void *free_env(t_env *env);

//Utils
void	ft_add_env_back(t_env **list, t_env *new_node);
char	*ft_get_env(char *key, t_env *env_list);

//Export (built-in)
t_env	*fill_export_env(char *env_str, t_env *env);
t_env	*new_env_var(char *arg, t_env **env_list);

// Env printing (built-in)
int env_builtin(t_env *env);
#endif