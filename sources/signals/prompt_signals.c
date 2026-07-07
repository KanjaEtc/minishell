#include "../../includes/minishell.h"

int g_var = 0; // Global variable to store the exit status of the last executed command

void prompt_sigint(int sig)
{
    if (sig == SIGINT)
    {
        g_var = 130;
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void setup_signals(void)
{
    signal(SIGINT, prompt_sigint);
    signal(SIGQUIT,SIG_IGN); // Ignore SIGQUIT (Ctrl+\)
}