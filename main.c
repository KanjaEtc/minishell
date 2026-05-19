#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av)
{
    (void)ac; (void)av;
    char *line;

    while (1)
    {
        line = readline("Minishell prompt> ");
        if (!line)
            break;
        if (line && *line)
            add_history(line);
        free(line); 
    }
    return 0;
}

// Sources :
// "https://man7.org/linux/man-pages/man3/readline.3.html"
// "https://i.sstatic.net/lVx5P.gif"
// "https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions"
