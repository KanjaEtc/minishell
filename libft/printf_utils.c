/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:20:50 by ranoumba          #+#    #+#             */
/*   Updated: 2026/03/29 20:54:58 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_nbr(int nb)
{
	long	n;
	int		i;

	n = (long)nb;
	i = 0;
	if (n < 0)
	{
		i += print_char('-');
		n = -n;
	}
	if (n > 9)
		i += print_nbr(n / 10);
	i += print_char(n % 10 + '0');
	return (i);
}

int	print_unsigned(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb > 9)
	{
		i += print_unsigned(nb / 10);
		i += print_unsigned(nb % 10);
	}
	else
	{
		print_char(nb + '0');
		i++;
	}
	return (i);
}

int	print_hex(unsigned long long n, char format)
{
	int		i;
	char	*base;

	i = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
		i += print_hex(n / 16, format);
	i += print_char(base[n % 16]);
	return (i);
}

int	print_ptr(void *ptr)
{
	unsigned long		n;
	int					i;

	n = (unsigned long)ptr;
	i = 0;
	if (!ptr)
		return (print_str("(nil)"));
	print_str("0x");
	i += 2;
	i += print_hex(n, 'x');
	return (i);
}
