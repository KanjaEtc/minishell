#include "../../includes/minishell.h"

static void	child_process(t_cmd *cmd, int *pipe_fd, int prev_fd, t_env *env)
{
	setup_child_signals(); 
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (apply_redirections(cmd->redirs) == -1)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		g_var = exec_builtin(cmd, &env);
		exit(g_var);
	}
	exec_simple_cmd(cmd, env);
}

static int	parent_close_fds(int prev_fd, int *pipe_fd, t_cmd *curr)
{
	if (prev_fd != -1)
			close(prev_fd);
	if (curr->next)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	else
		return (-1);
}

void	execute_pipeline(t_cmd *cmd_list, t_env *env)
{
	t_cmd	*curr;
	int		pipe_fd[2];
	int		prev_fd;
	int		status;
	pid_t	pid;
	pid_t last_pid;

	curr = cmd_list;
	prev_fd = -1;
	last_pid = -1;
	setup_exec_signals();
	while (curr)
	{
		if (curr->next && pipe(pipe_fd) == -1)
			return (perror("minishell: pipe failed"));
		pid = fork();
		if (pid == -1)
			return (perror("minishell: fork failed"));
		if (pid == 0)
			child_process(curr, pipe_fd, prev_fd, env);
		prev_fd = parent_close_fds(prev_fd, pipe_fd, curr);
		if (!curr->next)
			last_pid = pid;
		curr = curr->next;
	}
	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			g_var = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_var = 128 + WTERMSIG(status);
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	setup_signals();
}
