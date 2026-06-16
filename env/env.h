#ifndef ENV_H
# define ENV_H

#include <stdlib.h>
#include <stdio.h>
// #include "libft.h"

typedef struct s_env
{
    char			*key;
    char			*value;
    struct s_env	*next;
}	t_env;

void	print_env(t_env *env);
t_env	*init_env(char **envp);

//libft
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
size_t	ft_strlen(const char *str);


#endif