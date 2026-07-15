#include "../includes/minishell.h"
#include "../includes/debug_utils.h"

int main(int ac, char **av, char **envp)
{
	char *line;
	t_env *env;
	t_token *tokens;
	t_cmd	*cmds;

	
	(void)ac; (void)av;
	ft_putstr_fd("Welcome to minishell!\n", 1);
	env = env_set(envp);
	if (!env)
	{
		perror("Error: Failed to initialize environment variables.\n");
		return (1);
	}
	while (1)
	{
		setup_signals();
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break;
		}
		if (ft_strcmp(line, "exit") == 0)
		{
			ft_putstr_fd("exit\n", 1);
			free(line);
			break;
		}
		if (*line)
			add_history(line);
		else
		{
			free(line);
			continue;
		}
		tokens = lexer(line);
		if (!tokens)
		{
			free(line);
			continue;
		}
		assign_token_types(tokens);
		expand_tokens(tokens, env);
		cmds = parse_tokens(tokens);
		if (!cmds)
		{
			free_token(&tokens);
			free(line);
			continue;
		}
		exec_cmd(cmds, env);
		// t_cmd *tmp = cmds;
		// while (tmp)
		// {
		// 	printf("Commande prête : %s\n", tmp->args ? tmp->args[0] : "NULL");
		// 	tmp = tmp->next;
		// }
		free_token(&tokens);
		free(line);
	}
	rl_clear_history();
	free_env(env);
	free_token(&tokens);
	return 0;
}




// int main(int ac, char **av, char **envp)
// {
//     char *line;
//     t_env *env;
//     t_token *tokens;

	
//     (void)ac; (void)av;
//     ft_putstr_fd("Welcome to minishell!\n", 1);
//     env = env_set(envp);
//     if (!env)
//     {
//         perror("Error: Failed to initialize environment variables.\n");
//         return (1);
//     }
//     while (1)
//     {
//         setup_signals();
//         line = readline("minishell> ");
//         if (!line || ft_strcmp(line, "exit") == 0)
//         {
//             ft_putstr_fd("exit\n", 1);
//             break;
//         }
//         if (line && *line)
//             add_history(line);
//         else
//         {
//             free(line);
//             continue;
//         }
//         tokens = lexer(line);
//         if (!tokens)
//         {
//             free(line);
//             continue;
//         }
//         print_tokens(tokens);
//         // expand_tokens(tokens, env);
//         // free(line);
//     }
//     rl_clear_history();
//     free_env(env);
//     free_token(&tokens);
//     return 0;
// }

// Sources :
// "https://man7.org/linux/man-pages/man3/readline.3.html"
// "https://i.sstatic.net/lVx5P.gif"
// "https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions"
