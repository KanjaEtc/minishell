#include "../../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac; (void)av;
    char *line;
    t_env *env;
    
    
    ft_putstr_fd("Welcome to minishell!\n", 1);
    env = init_env(envp);
    if (!env)
    {
        ft_putstr_fd("Error: Failed to initialize environment variables.\n", 2);
        return (1);
    }
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
            break;
        if (line && *line)
            add_history(line);
        free(line);
        // if (unclosed_quote(line))//sers simplement a gerer le cas des quotes non fermees
        // {
        //     printf("Error: unclosed quote\n");
        //     free(line);
        // }
        // else
        // {
        //     t_token *tokens = lexer(line);
        //     //suite sera coder plus tard
        // }
    }
    rl_clear_history();
    free_env(env);
    return 0;
}

// Sources :
// "https://man7.org/linux/man-pages/man3/readline.3.html"
// "https://i.sstatic.net/lVx5P.gif"
// "https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions"
