/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:23:26 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/17 17:22:20 by ranoumba         ###   ########.fr       */
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

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	int	i;
	char	*final_s;
	int		len1;
	int		len2;
	int		len3;

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