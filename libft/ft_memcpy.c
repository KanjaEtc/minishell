/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:14:17 by ranoumba          #+#    #+#             */
/*   Updated: 2025/11/13 14:49:42 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest2;
	unsigned char	*src2;

	i = 0;
	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	if (!dest2 && !src2)
		return (NULL);
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest2);
}
/*
int main(void)
{
	char src[] = "geeks";
	char dest[] = "salut";

	printf("%s\n", dest);
//	printf("%s\n", (char *)ft_memcpy(dest, (void *)src, 6));
	printf("%s\n", (char *)memcpy(dest, src, 6));
}*/
