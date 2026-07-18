/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:08:06 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:08:06 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	delete_env_node(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_builtin(t_env **env, char **keys)
{
	int	i;
	int	ret;

	if (!keys || !env || !*env)
		return (0);
	i = 1;
	ret = 0;
	while (keys[i])
	{
		if (!is_valid_identifier(keys[i], 1))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(keys[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
		{
			delete_env_node(env, keys[i]);
		}
		i++;
	}
	return (ret);
}
