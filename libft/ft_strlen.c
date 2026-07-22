/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:57:30 by marotsen          #+#    #+#             */
/*   Updated: 2026/07/17 17:20:54 by ranoumba         ###   ########.fr       */
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
