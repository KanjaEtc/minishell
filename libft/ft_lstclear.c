/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:47:08 by ranoumba          #+#    #+#             */
/*   Updated: 2026/04/15 20:00:55 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;	

	if (!del)
		return ;
	if (lst)
	{
		current = *lst;
		while (current)
		{
			next = current -> next;
			ft_lstdelone(current, (del));
			current = next;
		}
		*lst = NULL;
	}
}
