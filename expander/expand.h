


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
