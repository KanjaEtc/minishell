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

typedef struct s_status
{
	status_type	status;
}	t_status;



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

/*************LEXER**********************/
t_token		*lexer(char *line);
t_token		*new_token(char *val, t_type type);
static void	handle_lexer_operators(char *line, int *i, int *start, t_token **token_list);
void		add_token_back(t_token **list, t_token *new_token);
void		free_token(t_token **list);

/*************LEXER_UTILS****************/
int			update_quote_status(char c, int curr_status);
int			unclosed_quote(char *line);
int			ft_strcmp(const char *s1,const char *s2);
void		assign_token_types(t_token *token_list);

/***************ENV_UTILS****************/
t_env		*init_env(char **envp);
t_env		*create_new_t_env(char *key, char *value);
void		ft_add_env_back(t_env **list, t_env *new_node);
char		*ft_get_env(char *key, t_env *env_list);

/***************EXPANDER_UTILS***********/
int			is_valid_var_char(char c);
int			var_len(char *str);
char		*ft_strjoin_three(char *s1, char *s2, char *s3);

/***************EXPANDER*****************/
void		expand_tokens(t_token *tokens, t_env *env);
char		*expand_string(char *str, t_env *env);
static char	*handle_dollar(char *str, int i, t_env *env);

/***************QUOTE_STRIPPER***********/
int	get_clean_len(char	*str);
char	*strip_quotes(char *str);

#endif