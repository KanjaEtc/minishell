/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marotsen <marotsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:57:30 by marotsen          #+#    #+#             */
/*   Updated: 2025/11/14 18:12:18 by marotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//This function calculates the length of the string pointed to by str, 
//excluding the terminating null byte.

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
