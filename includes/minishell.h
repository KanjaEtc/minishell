#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include "struct.h"
#include "../s_libft/s_libft.h"

int g_var = 0;

/*************LEXER*********************/
t_token		*lexer(char *line);
t_token		*new_token(char *val, t_type type);
// static void	handle_lexer_operators(char *line, int *i, int *start, t_token **token_list);
void		add_token_back(t_token **list, t_token *new_token);

/*************LEXER_UTILS***************/
int			update_quote_status(char c, int curr_status);
int			unclosed_quote(char *line);
void		assign_token_types(t_token *token_list);
void		free_token(t_token **list);

/*************ENV_SET*******************/
t_env	*fill_env(char *env_str, t_env *env);
t_env	*init_env(char **envp);

/*************ENV_UTILS*****************/
void		ft_add_env_back(t_env **list, t_env *new_node);
char		*ft_get_env(char *key, t_env *env_list);
void	print_env(t_env *env);
void *free_env(t_env *env);
char **env_to_envp(t_env *env);

/***************EXPANDER_UTILS***********/
int			is_valid_var_char(char c);
int			var_len(char *str);

/***************EXPANDER*****************/
void		expand_tokens(t_token *tokens, t_env *env);
char		*expand_string(char *str, t_env *env);
// static char	*handle_dollar(char *str, int i, t_env *env);

/***************QUOTE_STRIPPER***********/
int	get_clean_len(char	*str);
char	*strip_quotes(char *str);

/***************BUILT-INS****************/
//Export
t_env	*fill_export_env(char *env_str, t_env *env);
t_env	*new_env_var(char *arg, t_env **env_list);

// Env
int env_builtin(t_env *env);

// Echo
int echo_builtin(int argc, char **argv);

// PWD (built-in)
int pwd_builtin(t_env *env);


// Unset (built-in)
int unset_builtin(t_env **env, char **keys);

/***************SIGNALS****************/
void handle_sigint(int sig);
void setup_signals(void);

/**************EXECUTION***************/
int is_builtin(char *cmd);
void exec_builtin(t_cmd *cmd, t_env **env);
int exec_execve(t_cmd *cmd, t_env *env);
void exec_cmd(t_cmd *cmd, t_env **env);
char *get_path(char *cmd, t_env *env);

#endif