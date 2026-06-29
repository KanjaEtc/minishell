typedef struct s_cmd
{
    char			*cmd;
    char			**args;
    struct s_cmd	*next;
}	t_cmd;