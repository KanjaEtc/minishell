/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 03:11:07 by marotsen          #+#    #+#             */
/*   Updated: 2026/07/17 17:21:44 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//This function copies n bytes from memory area src to memory area dest.
//The memory areas must not overlap.

#include "libft.h"
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dptr;
	unsigned char	*sptr;
	size_t			i;

	dptr = (unsigned char *)dest;
	sptr = (unsigned char *)src;
	i = 0;
	if (dest == 0 && src == 0)
		return (dest);
	while (i < n)
	{
		dptr[i] = sptr[i];
		i++;
	}
	return (dest);
}
