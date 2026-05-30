/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:18:48 by ranoumba          #+#    #+#             */
/*   Updated: 2026/03/29 20:55:03 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_format(va_list va, char *str, int *count)
{
	if (*str == 'c')
		*count += print_char(va_arg(va, int));
	else if (*str == 's')
		*count += print_str(va_arg(va, char *));
	else if (*str == 'p')
		*count += print_ptr(va_arg(va, void *));
	else if (*str == 'd' || *str == 'i')
		*count += print_nbr(va_arg(va, int));
	else if (*str == 'u')
		*count += print_unsigned(va_arg(va, unsigned long));
	else if (*str == 'x')
		*count += print_hex(va_arg(va, unsigned int), 'x');
	else if (*str == 'X')
		*count += print_hex(va_arg(va, unsigned int), 'X');
	else if (*str == '%')
		*count += print_char(*str);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		va;
	int			count;

	va_start(va, str);
	if (!str)
		return (-1);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_format(va, (char *)str, &count);
		}
		else
		{
			print_char(*str);
			count++;
		}
		str++;
	}
	va_end(va);
	return (count);
}
/*
int main(void)
{
	ft_printf("%d\n", ft_printf(" %u ", -1));
	printf("%d\n", printf(" %u ", -1));
	return (1);
}
*/
