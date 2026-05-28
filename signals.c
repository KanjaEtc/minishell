#include "minishell.h"

int g_var = 0;

void handle_sigint(int sig)
{
    (void)sig;

    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();                 
}

void handle_sigquit(int sig)
{
    (void)sig;
    write(1, "Quit: 3\n", 8);
}

void setup_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
}