#ifndef STRUCT_H
# define STRUCT_H

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

typedef enum e_status_type
{
	IN_D_QUOTES,
	IN_S_QUOTES,
	NO_QUOTES,
}	status_type;

typedef struct s_status
{
	status_type	status;
}	t_status;

typedef struct s_cmd
{
    char			*cmd;
    char			**args;
    struct s_cmd	*next;
}	t_cmd;

#endif