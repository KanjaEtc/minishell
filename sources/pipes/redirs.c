/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranoumba <ranoumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 20:11:44 by ranoumba          #+#    #+#             */
/*   Updated: 2026/07/20 21:39:05 by marotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_redir_file(char *filename, t_type type)
{
	int	fd;

	fd = -1;
	if (type == RED_IN)
		fd = open(filename, O_RDONLY);
	else if (type == RED_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

static int	execute_redir(t_token *curr)
{
	int	fd;

	if (curr->next && curr->next->invalid_redir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(curr->next->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	if (curr->type == HEREDOC)
		fd = handle_heredoc(curr->next->value);
	else
		fd = open_redir_file(curr->next->value, curr->type);
	if (fd == -1)
		return (perror("minishell: redirection failed"), -1);
	if (curr->type == RED_IN || curr->type == HEREDOC)
		dup2(fd, STDIN_FILENO);
	else if (curr->type == RED_OUT || curr->type == APPEND)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_token *redirs)
{
	t_token	*curr;

	curr = redirs;
	while (curr)
	{
		if (curr->next)
		{
			if (execute_redir(curr) == -1)
				return (-1);
			curr = curr->next->next;
		}
		else
			curr = curr->next;
	}
	return (0);
}

void	unlink_temporary_heredocs(t_cmd *cmds)
{
	t_cmd	*curr_cmd;
	t_token	*curr_redir;

	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redirs;
		while (curr_redir)
		{
			if (curr_redir->type == RED_IN && ft_strncmp(curr_redir->value,
					"/tmp/.minishell_hd_", 19) == 0)
				unlink(curr_redir->value);
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
