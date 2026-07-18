/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 19:43:10 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/18 19:43:10 by ranoumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute_parsed_commands(t_cmd *cmds, t_env **env)
{
	exec_all_heredocs(cmds);
	if (cmds->next)
		execute_pipeline(cmds, env);
	else
		exec_cmd(cmds, env);
	unlink_temporary_heredocs(cmds);
}

static void	process_line(char *line, t_env **env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	if (!tokens)
		return ;
	if (check_syntax_errors(tokens))
	{
		free_token(&tokens);
		return ;
	}
	expand_tokens(&tokens, *env);
	clean_empty_tokens(&tokens);
	clean_all_tokens(tokens);
	cmds = parse_tokens(tokens);
	if (cmds)
	{
		execute_parsed_commands(cmds, env);
		free_cmd_table(cmds);
	}
	free_token(&tokens);
}

static void	run_shell_loop(t_env **env)
{
	char	*line;

	while (1)
	{
		setup_signals();
		line = readline("minishell> ");
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*line)
		{
			add_history(line);
			process_line(line, env);
		}
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	(void)av;
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
