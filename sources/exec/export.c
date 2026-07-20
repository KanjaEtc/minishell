/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:05:39 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:05:39 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_no_args(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (curr->value)
			printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
		else
			printf("declare -x %s\n", curr->key);
		curr = curr->next;
	}
	return (0);
}

static int	execute_export(t_env **env_list, char *key, char *val, int has_sep)
{
	t_env	*curr;

	curr = *env_list;
	while (curr && ft_strcmp(curr->key, key) != 0)
		curr = curr->next;
	if (curr)
	{
		if (has_sep)
		{
			free(curr->value);
			curr->value = val;
		}
		else
			free(val);
		free(key);
	}
	else
	{
		curr = create_env_node(key, val);
		if (curr)
			ft_add_env_back(env_list, curr);
		else
		{
			free(val);
			free(key);
			return (1);
		}
	}
	return (0);
}

int	export_builtin(char *env_str, t_env **env_list)
{
	char	*sep;
	char	*key;
	char	*val;

	if (!is_valid_identifier(env_str, 0))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(env_str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	sep = ft_strchr(env_str, '=');
	if (sep)
		key = ft_substr(env_str, 0, sep - env_str);
	else
		key = ft_strdup(env_str);
	val = NULL;
	if (sep)
		val = ft_strdup(sep + 1);
	return (execute_export(env_list, key, val, (sep != NULL)));
}

int	dispatch_export(t_cmd *cmd, t_env **env)
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