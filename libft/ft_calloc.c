/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:58:56 by ranoumba          #+#    #+#             */
/*   Updated: 2026/03/29 21:00:05 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tab;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb / INT_MAX > size)
		return (0);
	tab = malloc(size * nmemb);
	if (!tab)
		return (0);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
