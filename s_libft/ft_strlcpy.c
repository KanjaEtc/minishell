/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marotsen <marotsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:44:11 by marotsen          #+#    #+#             */
/*   Updated: 2025/11/15 19:29:25 by marotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//This function copies up to siz - 1 characters from the string src to dst,
//null-terminating the result if siz is not 0.

#include "s_libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < siz)
		ft_memcpy(dst, src, srclen + 1);
	else if (siz != 0)
	{
		ft_memcpy(dst, src, siz - 1);
		dst[siz - 1] = 0;
	}
	return (srclen);
}
