/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marotsen <marotsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:45:13 by marotsen          #+#    #+#             */
/*   Updated: 2025/11/14 19:16:21 by marotsen         ###   ########.fr       */
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
