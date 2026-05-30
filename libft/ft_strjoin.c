/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:23:26 by ranoumba          #+#    #+#             */
/*   Updated: 2025/11/13 22:06:25 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*finalstr;
	int		len1;
	int		len2;
	int		i;
	int		j;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	i = -1;
	j = -1;
	finalstr = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!finalstr)
		return (0);
	while (s1[++i])
		finalstr[i] = s1[i];
	while (s2[++j])
		finalstr[i + j] = s2[j];
	finalstr[i + j] = '\0';
	return (finalstr);
}
