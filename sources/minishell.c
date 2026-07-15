#include "../includes/minishell.h"
#include "../includes/debug_utils.h"


#include "../includes/minishell.h"
#include "../includes/debug_utils.h"

// int main(int ac, char **av, char **envp)
// {
// 	char    *line;
// 	t_env   *env;
// 	t_token *tokens;
// 	t_cmd	*cmds;

// 	(void)ac; (void)av; 
// 	env = env_set(envp); 
// 	if (!env)
// 	{
// 		perror("Error: Failed to initialize environment variables.\n"); 
// 		return (1); 
// 	}
// 	while (1)
// 	{
// 		tokens = NULL;
// 		cmds = NULL;
// 		setup_signals(); 
// 		line = readline("minishell> "); 
// 		if (!line)
// 		{
// 			if (isatty(STDIN_FILENO))
// 				ft_putstr_fd("exit\n", 1); 
// 			break;
// 		}
// 		if (*line)
// 			add_history(line); 
// 		else
// 		{
// 			free(line); 
// 			continue; 
// 		}
// 		tokens = lexer(line); 
// 		if (!tokens)
// 		{
// 			free(line); 
// 			continue; 
// 		}
// 		expand_tokens(tokens, env); 
// 		cmds = parse_tokens(tokens); 
// 		if (!cmds)
// 		{
// 			free_token(&tokens); 
// 			free(line); 
// 			continue; 
// 		}
// 		if (cmds->next)
// 			execute_pipeline(cmds, env);
// 		else
// 			exec_cmd(cmds, env);
// 		free_token(&tokens); 
// 		free_cmd_table(cmds);
// 		free(line); 
// 	}
// 	rl_clear_history(); 
// 	free_env(env); 
// 	return (0);
// }

int main(int ac, char **av, char **envp)
{
	char    *line;
	t_env   *env;
	t_token *tokens;
	t_cmd	*cmds;

	(void)ac; (void)av;
	env = env_set(envp);
	if (!env)
	{
		perror("Error: Failed to initialize environment variables.\n");
		return (1);
	}
	while (1)
	{
		tokens = NULL;
		cmds = NULL;
		setup_signals();
		
		// Hide the prompt prefix when the tester runs non-interactively
		if (isatty(STDIN_FILENO))
			line = readline("minishell> ");
		else
			line = readline(NULL);
			
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", 1);
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
		expand_tokens(tokens, env);
		cmds = parse_tokens(tokens);
		if (!cmds)
		{
			free_token(&tokens);
			free(line);
			continue;
		}
		if (cmds->next)
			execute_pipeline(cmds, env);
		else
			exec_cmd(cmds, env);
		free_token(&tokens);
		free_cmd_table(cmds);
		free(line);
	}
	rl_clear_history();
	free_env(env);
	return (0);
}

// Sources :
// "https://man7.org/linux/man-pages/man3/readline.3.html"
// "https://i.sstatic.net/lVx5P.gif"
// "https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions"
