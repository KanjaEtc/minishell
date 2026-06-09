#include "minishell.h"

int	is_valid_var_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	var_len(char *str)
{
	int	i;

	if (str[0] == '?')
		return (1);
	i = 0;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	return (i);
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	int	i;
	char	*final_s;
	int		len1;
	int		len2;
	int		len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	final_s = malloc(sizeof(char) * (len1 + len2 + len3 +1));
	if (!final_s)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		final_s[i++] = *s1++;
	while (s2 && *s2)
		final_s[i++] = *s2++;
	while (s3 && *s3)
		final_s[i++] = *s3++;
	final_s[i] = '\0';
	return (final_s);
}



