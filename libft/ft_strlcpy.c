/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:04:06 by ranoumba          #+#    #+#             */
/*   Updated: 2025/11/13 10:40:29 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len;

	len = ft_strlen((char *)src);
	if (size == 0)
		return (len);
	i = 0;
	while (src[i] != '\0' && (i < size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
/*
int	main(void)
{
	char dest[100];
	char src[] = "salut";

	printf("%s", src);
	printf("%s", "\n");
	Uprintf("%zu", ft_strlcpy(dest, src, 3));
	printf("%s", "\n");
	printf("%s", dest);
}*/
