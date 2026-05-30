/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:36:44 by ranoumba          #+#    #+#             */
/*   Updated: 2025/11/13 14:48:03 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j < len))
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (0);
}
/*#include <string.h>
int     main(void)
{
        char    *hello = "Hello, how are you? Bye.";
//        char    *how = "how";

//        how = ft_strstr (hello, "how are");
//      printf("%s\n", how);
	printf("%s\n", ft_strnstr(hello, "how are", 20));
//	printf("%s\n", strnstr(hello, "how are", 5));
}
*/
