/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 19:43:10 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 22:08:20 by marotsen         ###   ########.fr       */
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

static void	run_cmds(t_shell *shell)
{
	if (exec_all_heredocs(shell->cmds) == -1)
	{
		free_cmd_table(shell->cmds);
		shell->cmds = NULL;
		return ;
	}
	execute_parsed_commands(shell->cmds, &shell->env);
	unlink_temporary_heredocs(shell->cmds);
	free_cmd_table(shell->cmds);
	shell->cmds = NULL;
}

static void	process_line(char *line, t_shell *shell)
{
	if (!line || !*line)
		return ;
	if (unclosed_quote(line))
	{
		g_var = 2;
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return ;
	}
	shell->tokens = lexer(line);
	if (!shell->tokens || check_syntax_errors(shell->tokens))
		return ;
	expand_tokens(&shell->tokens, shell->env);
	clean_empty_tokens(&shell->tokens);
	clean_all_tokens(shell->tokens);
	shell->cmds = parse_tokens(shell->tokens);
	if (shell->cmds)
		run_cmds(shell);
	if (shell->tokens)
		free_token(&shell->tokens);
}

static void	run_shell_loop(t_shell *shell)
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
			process_line(line, shell);
		}
		free(line);
		shell->line = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	ft_bzero(shell, sizeof(t_shell));
	get_shell(shell);
	shell->env = env_set(envp);
	if (!shell->env)
	{
		perror("Error: Failed to initialize environment variables.\n");
		free(shell);
		return (1);
	}
	run_shell_loop(shell);
	rl_clear_history();
	free_env(shell->env);
	free(shell);
	return (g_var);
}
