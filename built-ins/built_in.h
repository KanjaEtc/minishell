#ifndef BUILT_IN_H
# define BUILT_IN_H

//Export (built-in)
t_env	*fill_export_env(char *env_str, t_env *env);
t_env	*new_env_var(char *arg, t_env **env_list);

// Env (built-in)
int env_builtin(t_env *env);

// Echo (built-in)
int echo_builtin(int argc, char **argv, int option);

#endif