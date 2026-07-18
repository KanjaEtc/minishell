/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 19:21:23 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 19:29:39 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*final_s;
	int		len1;
	int		len2;
	int		len3;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	final_s = malloc(sizeof(char) * (len1 + len2 + len3 +1));
	if (!final_s)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		final_s[i++] = *s1++;
	while (s2 && *s2)
		final_s[i++] = *s2++;
	while (s3 && *s3)
		final_s[i++] = *s3++;
	final_s[i] = '\0';
	return (final_s);
}
