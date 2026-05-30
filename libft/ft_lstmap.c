/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:50:12 by ranoumba          #+#    #+#             */
/*   Updated: 2025/11/18 15:11:57 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*new;
	void	*data;

	map = 0;
	if (!f || !del)
		return (0);
	while (lst)
	{
		data = f(lst -> content);
		new = ft_lstnew(data);
		if (!new)
		{
			if (data)
				del(data);
			ft_lstclear(&map, del);
		}
		ft_lstadd_back(&map, new);
		lst = lst -> next;
	}
	return (map);
}
