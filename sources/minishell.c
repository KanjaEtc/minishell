#include "../includes/minishell.h"
#include "../includes/debug_utils.h"

static char	*get_next_line_fallback(int fd)
{
	char	buf[2];
	char	*line;
	char	*temp;
	int		bytes;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		bytes = read(fd, buf, 1);
		if (bytes <= 0)
			break ;
		buf[1] = '\0';
		if (buf[0] == '\n')
			break ;
		temp = ft_strjoin(line, buf);
		free(line);
		line = temp;
	}
	if (bytes <= 0 && ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

static void	run_shell_loop(t_env **env)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	while (1)
	{
		setup_signals();
		if (isatty(STDIN_FILENO))
			line = readline("minishell> ");
		else
			line = get_next_line_fallback(STDIN_FILENO);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*line)
			add_history(line);
		else
		{
			free(line);
			continue ;
		}
		tokens = lexer(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		if (check_syntax_errors(tokens))
		{
			free_token(&tokens);
			free(line);
			continue ;
		}
		expand_tokens(&tokens, *env);
		clean_empty_tokens(&tokens);
		clean_all_tokens(tokens)
;		cmds = parse_tokens(tokens);
		if (!cmds)
		{
			free_token(&tokens);
			free(line);
			continue ;
		}
		exec_all_heredocs(cmds);
		if (cmds->next)
			execute_pipeline(cmds, env);
		else
			exec_cmd(cmds, env);
		unlink_temporary_heredocs(cmds);
		free_token(&tokens);
		free_cmd_table(cmds);
		free(line);
	}
}

int main(int ac, char **av, char **envp)
{
	t_env   *env;

	(void)ac; (void)av;
	env = env_set(envp);
	if (!env)
	{
		perror("Error: Failed to initialize environment variables.\n");
		return (1);
	}
	run_shell_loop(&env);
	rl_clear_history();
	free_env(env);
	return (0);
}

// Sources :
// "https://man7.org/linux/man-pages/man3/readline.3.html"
// "https://i.sstatic.net/lVx5P.gif"
// "https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions"
