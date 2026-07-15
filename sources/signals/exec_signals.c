#include "../../includes/minishell.h"

void	setup_exec_signals(void)
{
	signal(SIGINT, SIG_IGN);  
	signal(SIGQUIT, SIG_IGN); 
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);  
	signal(SIGQUIT, SIG_DFL); 
}