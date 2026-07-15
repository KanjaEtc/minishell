#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "struct.h"
#include "../s_libft/s_libft.h"
// #include "../libft/libft.h"

extern int g_var; // Global variable to hold the exit status

/*************LEXER*********************/
t_token	*lexer(char *line);
t_token	*new_token(char *val, t_type type);
void	add_token_back(t_token **list, t_token *new_token);

/*************LEXER_UTILS***************/
int		update_quote_status(char c, int curr_status);
int		unclosed_quote(char *line);
void	assign_token_types(t_token *token_list);
void	free_token(t_token **list);

/*************ENV_SET*******************/
t_env	*fill_env(char *env_str, t_env *env);
t_env	*init_env(char **envp);
t_env	*empty_env(void);
t_env	*env_set(char **envp);


/*************ENV_UTILS*****************/
void	ft_add_env_back(t_env **list, t_env *new_node);
char	*ft_get_env(char *key, t_env *env_list);
void	print_env(t_env *env);
void	*free_env(t_env *env);
char	**env_to_envp(t_env *env);

/***************EXPANDER_UTILS***********/
int		is_valid_var_char(char c);
int		var_len(char *str);

/***************EXPANDER*****************/
void	expand_tokens(t_token *tokens, t_env *env);
char	*expand_string(char *str, t_env *env);
char	*handle_dollar(char *str, int i, t_env *env);

/***************QUOTE_STRIPPER***********/
int	    get_clean_len(char	*str);
char	*strip_quotes(char *str);

/***************BUILT-INS****************/
t_env	*export_builtin(char *env_str, t_env *env);
t_env	*new_env_var(char *arg, t_env **env_list);
int		env_builtin(t_env *env);
int		echo_builtin(int argc, char **argv);
int		pwd_builtin(t_env *env);
int		cd_builtin(t_env *env, char **args);
int		unset_builtin(t_env *env, char **keys);

/***************SIGNALS****************/
void	prompt_sigint(int sig);
void	setup_signals(void);

/**************EXECUTION***************/
int		is_builtin(char *cmd);
void	exec_builtin(t_cmd *cmd, t_env *env);
// int exec_execve(t_cmd *cmd, t_env *env);
void	exec_cmd(t_cmd *cmd, t_env *env);
char	*get_path(char *cmd, t_env *env);
void	exec_simple_cmd(t_cmd *cmd, t_env *env);

/*****************PARSER**********************/
t_cmd	*parse_tokens(t_token *tokens);

/*****************PARSER_UTILS****************/
t_cmd	*lst_new_cmd(void);
void	free_cmd_table(t_cmd *cmd);
int		count_arg(t_token *tokens);
char	**get_cmd_args(t_token *tokens);
void	add_cmd_back(t_cmd **list, t_cmd *new_cmd);

/*************PARSER_UTILS_BIS****************/
t_token	*copy_token(t_token *src);
void	add_redir_node(t_token **redirs, t_token *curr);

/********************PIPES********************/
int		apply_redirections(t_token *redirs);
void	execute_pipeline(t_cmd *cmd_list, t_env *env);
int		handle_heredoc(char *limiter);

#endif