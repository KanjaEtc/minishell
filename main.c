#include "minishell.h"

int main(int ac, char **av)
{
    (void)ac; (void)av;
    char *line;

    while (1)
    {
        line = readline("minishell> ");
        if (!line)
            break; 
        if (line && *line)
            add_history(line);
        free(line);
    }
    rl_clear_history();
    return 0;
}

// Sources :
// "https://man7.org/linux/man-pages/man3/readline.3.html"
// "https://i.sstatic.net/lVx5P.gif"
// "https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions"
