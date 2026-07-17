/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:45:13 by marotsen          #+#    #+#             */
/*   Updated: 2026/07/17 17:21:23 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//This function locates the first occurrence of c in the string pointed to by str.

//It returns a pointer to the located character, 
//or NULL if the character does not appear in the string.

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == ((unsigned char)c))
		return ((char *)&str[i]);
	return (NULL);
}
