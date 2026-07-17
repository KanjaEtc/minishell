#include "../../includes/minishell.h"

static void update_env_var(t_env *env, char *key, char *value)
{
	t_env *curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return;
		}
		curr = curr->next;
	}
}

static int	handle_cd_home(t_env *env, char **path)
{
	char	*home;

	home = ft_get_env("HOME", env);
	if (home == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	*path = home;
	return (0);
}

static int	handle_cd_oldpwd(t_env *env, char **path)
{
	char    *oldpwd;

	oldpwd = ft_get_env("OLDPWD", env);
	if (oldpwd == NULL)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		return (1);
	}
	*path = oldpwd;
	return (0);
}

int	cd_builtin(t_env *env, char **args)
{
	char *path;
	char cwd[1024];
	char old_cwd[1024];

	if (!getcwd(old_cwd, sizeof(old_cwd)))
		old_cwd[0] = '\0';
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		if (handle_cd_home(env, &path))
			return (1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (handle_cd_oldpwd(env, &path))
			return (1);
	}
	else
		path = args[1]; 
	if (chdir(path) != 0) 
	{
		perror("minishell: cd");
		return (1); 
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (old_cwd[0] != '\0')
			update_env_var(env, "OLDPWD", old_cwd);
		update_env_var(env, "PWD", cwd);
	}
	return (0); 
}
