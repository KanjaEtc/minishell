/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marotsen <marotsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:18:34 by marotsen          #+#    #+#             */
/*   Updated: 2025/11/13 18:39:47 by marotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//This function allocates sufficient memory for a copy of the string src,
//copies the string, and returns a pointer to it.

//The memory allocated for the new string should be freed by the caller.

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char	*dup;

	dup = NULL;
	dup = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_strcpy(dup, src);
	return (dup);
}
