#include "../../includes/minishell.h"

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(char **args, t_env *env)
{
	long long	exit_code;

	ft_putendl_fd("exit", 1); // Exit always prints "exit" to stdout
	if (!args || !args[0] || !args[1])
	{
		// Clean up your environment before exiting to keep leaks at 0!
		free_env(env);
		exit(g_var); // Exit with the last command's status[cite: 10]
	}
	if (!is_all_digit(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		free_env(env);
		exit(255);
	}
	if (args[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1); // Do NOT exit the shell if there are too many args!
	}
	exit_code = ft_atoi(args[1]); // Ensure your atoi handles sign
	free_env(env);
	exit(exit_code % 256);
}
