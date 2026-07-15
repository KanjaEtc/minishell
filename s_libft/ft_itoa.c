/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:24:11 by ranoumba          #+#    #+#             */
/*   Updated: 2025/11/17 11:52:24 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_libft.h"

int	ft_len(int n)
{
	int		count;
	long	ln;

	ln = n;
	count = 0;
	if (n == 0)
		count++;
	if (ln < 0)
	{
		count++;
		ln = -ln;
	}
	while (ln > 0)
	{
		count++;
		ln /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int				size;
	unsigned long	nb;
	char			*tab;

	size = ft_len(n);
	tab = malloc(size + 1);
	nb = (unsigned long)n;
	if (!tab)
		return (0);
	tab[size] = '\0';
	if (n < 0)
	{
		tab[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		tab[--size] = '0';
	while (nb > 0)
	{
		tab[--size] = (nb % 10) + '0';
		nb /= 10;
	}
	return (tab);
}
