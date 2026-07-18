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

static int	dispatch_export(t_cmd *cmd, t_env **env)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!cmd->args[1])
		return (export_no_args(*env));
	while (cmd->args[i])
	{
		if (export_builtin(cmd->args[i], env) == 1)
			ret = 1;
		i++;
	}
	return (ret);
}

int	exec_builtin(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (echo_builtin(cmd->args));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd_builtin(*env, cmd->args));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd_builtin(*env));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (dispatch_export(cmd, env));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset_builtin(env, cmd->args));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env_builtin(*env));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (exit_builtin(cmd->args, env));
	return (0);
}

static void	clean_exit(int code, t_env **env)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
	if (env)
		free_env(*env);
	exit(code);
}

int	exit_builtin(char **args, t_env **env)
{
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 1);
	if (!args || !args[1])
		clean_exit(g_var, env);
	if (!is_num(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean_exit(2, env);
	}
	if (args[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	clean_exit((unsigned char)ft_atoi(args[1]), env);
	return (0);
}
