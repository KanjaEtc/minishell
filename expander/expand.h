#ifndef EXPAND_H
# define EXPAND_H

#include <stdlib.h>
#include <stdio.h>
#include "../env/env.h"
#include "../libft_stripped/libft_stripped.h"

typedef enum e_status_type
{
	IN_D_QUOTES,
	IN_S_QUOTES,
	NO_QUOTES,
}	status_type;

/***************EXPANDER_UTILS***********/
int			is_valid_var_char(char c);
int			var_len(char *str);
char		*ft_strjoin_three(char *s1, char *s2, char *s3);
int	        ft_strcmp(const char *s1,const char *s2);

/***************EXPANDER*****************/
// void		expand_tokens(t_token *tokens, t_env *env);
// char		*expand_string(char *str, t_env *env);
static char	*handle_dollar(char *str, int i, t_env *env);

#endif