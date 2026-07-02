/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:17:41 by ranoumba          #+#    #+#             */
/*   Updated: 2025/11/15 21:45:11 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_libft.h"

size_t	ft_countwords(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i] != 0) && (s[i + 1] == c || s[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

static int	skip_sep(char *s, char c, int j)
{
	while (s[j] == c)
		j++;
	return (j);
}

char	*ft_wordseparator(char *s, char c, int *j)
{
	int	start;
	int	len;

	len = 0;
	*j = skip_sep(s, c, *j);
	start = *j;
	while (s[*j] && s[*j] != c)
	{
		(*j)++;
		len++;
	}
	return (ft_substr(s, start, len));
}

char	**ft_split(char *s, char c)
{
	char	**dest;
	int		i;
	int		j;
	int		words;

	words = ft_countwords(s, c);
	dest = malloc(sizeof(char *) * (words + 1));
	if (!dest)
		return (0);
	i = 0;
	j = 0;
	while (i < words)
	{
		dest[i] = ft_wordseparator(s, c, &j);
		if (!dest[i])
		{
			while (--i >= 0)
				free(dest[i]);
			free(dest);
			return (NULL);
		}
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/*

char    *ft_wordseparator(char *s, char c, int *j)
{
    int     i;
    int     len;
    int     start;
    char    *string;

    i = 0;
    while (s[i] == c || s[i] == '\0')
        i++;
    len = 0;
    start = i;
    while (s[i] != c && s[i])
    {
        len++;
        i++;
    }
    *j += i;
    string = ft_substr(s, start, len);
    return (Istring);
}
int main(int ac, char **av)
{
	char	**array;
	int		i;
	
	if (ac != 3)
		return (0);

	array = ft_split(av[1], av[2][0]);
	i = -1;
	while (array[++i])
	{
		printf("%s\n", array[i]);
		free(array[i]);
	}
	free(array);
	return (0);
}*/
