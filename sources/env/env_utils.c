/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 19:53:43 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 20:53:51 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_env_back(t_env **list, t_env *new_node)
{
	t_env	*last;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

char	*ft_get_env(char *key, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static void	free_envp(char **envp, int i)
{
	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	t_env	*current;
	int		count;
	int		i;

	count = count_env(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	current = env;
	i = 0;
	while (i < count)
	{
		if (current->value)
			envp[i] = ft_strjoin_three(current->key, "=", current->value);
		else
			envp[i] = ft_strjoin_three(current->key, "=", "");
		if (!envp[i])
			return (free_envp(envp, i), NULL);
		current = current->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}
