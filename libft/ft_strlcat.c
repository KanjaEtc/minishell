/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:31:11 by ranoumba          #+#    #+#             */
/*   Updated: 2025/11/10 10:57:32 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	lend;
	unsigned int	lens;

	lend = ft_strlen(dest);
	lens = ft_strlen((char *)src);
	i = 0;
	if (size <= lend)
		return (size + lens);
	while (src[i] && (i + lend) < (size - 1))
	{
		dest[lend + i] = src[i];
		i++;
	}
	if (i < size)
		dest[lend + i] = '\0';
	return (lend + lens);
}
/*
int     main(void)
{
        char    mess[6] = "Hello";
        int     len;

        len = ft_strlcat(mess, " how r u? bye", 12);
        printf("%s\n%d character\n", mess, len);
}*/
