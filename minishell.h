#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;


typedef enum e_token_type
{
	WORD,
	PIPE,
	RED_IN,
	RED_OUT,
	APPEND,
	HEREDOC,
}	t_type;

typedef struct s_token
{
	char	*value;
	t_type		type;
	struct s_token *next;
}	t_token;

/*************TOKEN**********************/
t_token	*lexer(char *line);
void	assign_token_types(t_token *token_list);


/*************TOKEN_UTILS****************/
t_token	*new_token(char *val, t_type type);
void	add_token_back(t_token **list, t_token *new_token);
void	free_token(t_token **list);
int		ft_strcmp(const char *s1,const char *s2);

/*************LEXER_UTILS****************/
int	update_quote_status(char c, int curr_status);
int	unclosed_quote(char *line);

/***************ENV_UTILS****************/
t_env	*create_new_t_env(char *key, char *value);
void	ft_add_env_back(t_env **list, t_env *new_node);

#endif