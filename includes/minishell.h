/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 19:33:27 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 22:45:48 by marotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "struct.h"
# include "../libft/libft.h"

extern int	g_var;

/***************BUILT-INS****************/
int		cd_builtin(t_env *env, char **args);
int		echo_builtin(char **argv);
int		env_builtin(t_env *env);
int		exit_builtin(char **args, t_env **env);
int		export_no_args(t_env *env);
int		export_builtin(char *env_str, t_env **env_list);
int		dispatch_export(t_cmd *cmd, t_env **env);
int		pwd_builtin(t_env *env);
int		unset_builtin(t_env **env, char **keys);

void	close_extra_fds(void);

/*************ENVIRONMENT*****************/
t_env	*fill_env(char *env_str, t_env *env);
t_env	*init_env(char **envp);
t_env	*empty_env(void);
t_env	*env_set(char **envp);
t_env	*create_env_node(char *key, char *value);

t_shell	*get_shell(t_shell *set_shell);

void	*free_env(t_env *env);
void	ft_add_env_back(t_env **list, t_env *new_node);

char	*ft_get_env(char *key, t_env *env_list);
char	**env_to_envp(t_env *env);

int		is_valid_identifier(char *str, int is_unset);

/*************EXECUTION****************/
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_env **env);
int		find_executable_path(char *cmd, char **env_paths, char **path);
int     check_direct_path(char *cmd);

void	exec_single_builtin(t_cmd *cmd, t_env **env);
void	exec_simple_cmd(t_cmd *cmd, t_env *env);
void	exec_cmd(t_cmd *cmd, t_env **env);

char	*build_path(char *dir, char *cmd);
char	*search_in_paths(char *cmd, char **env_paths, int *has_perm);

void	free_envp(char **envp, int i);
void	free_envp2(char **envp);

/***************PARSING***********/
t_token	*lexer(char *line);
t_token	*new_token(char *val, t_type type);
t_token	*copy_token(t_token *src);
t_token	*split_expanded(char *str);

t_cmd	*lst_new_cmd(void);
t_cmd	*parse_tokens(t_token *tokens);

int		is_valid_var_char(char c);
int		var_len(char *str);
int		update_quote_status(char c, int curr_status);
int		unclosed_quote(char *line);
int		count_arg(t_token *tokens);
int		get_clean_len(char	*str);
int		check_syntax_errors(t_token *tokens);
int		has_unquoted_space(char *str);

void	clean_empty_tokens(t_token **tokens);
void	expand_tokens(t_token **tokens, t_env *env);
void	assign_token_types(t_token *token_list);
void	add_token_back(t_token **list, t_token *new_token);
void	add_redir_node(t_token **redirs, t_token *curr);
void	add_cmd_back(t_cmd **list, t_cmd *new_cmd);
void	free_cmd_table(t_cmd *cmd);
void	clean_all_tokens(t_token *tokens);
void	insert_split_tokens(t_token **head, t_token *curr, t_token *sub);

char	*expand_string(char *str, t_env *env);
char	*handle_dollar(char *str, int *i, t_env *env);
char	**get_cmd_args(t_token *tokens);
char	*strip_quotes(char *str);

/********************PIPES********************/
int		exec_all_heredocs(t_cmd *cmds);
int		handle_heredoc(char *limiter);
int		apply_redirections(t_token *redirs);

char	*read_heredoc_line(void);

void	execute_pipeline(t_cmd *cmd_list, t_env **env);
void	unlink_temporary_heredocs(t_cmd *cmds);

/***************SIGNALS****************/
void	prompt_sigint(int sig);
void	setup_signals(void);
void	setup_exec_signals(void);
void	setup_child_signals(void);
void	handle_sigint_heredoc(int sig);

/**************CLEANUP*****************/
void	clean_shell(t_shell *shell);
// void	free_envp(char **envp);
void	free_split(char **split);
void	free_token(t_token **list);
void	clean_and_exit(int status);

#endif
