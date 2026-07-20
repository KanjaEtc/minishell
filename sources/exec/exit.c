/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:05:26 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:05:26 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_num(char *str)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		has_digit = 1;
		i++;
	}
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] != '\0' || !has_digit)
		return (0);
	return (1);
}

static void	close_extra_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		if (fcntl(fd, F_GETFD) != -1)
			close(fd);
		fd++;
	}
}

void	clean_and_exit(int status)
{
	t_shell	*shell;

	shell = get_shell(NULL);
	close_extra_fds();
	clean_shell(shell);
	rl_clear_history();
	exit(status);
}
int	exit_builtin(char **args, t_env **env)
{
	int	code;

	(void)env;
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 1);
	if (!args || !args[1])
	{
		code = g_var;
		clean_and_exit(code);
	}
	if (!is_num(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean_and_exit(2);
	}
	if (args[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	code = (unsigned char)ft_atoi(args[1]);
	clean_and_exit(code);
	return (code);
}