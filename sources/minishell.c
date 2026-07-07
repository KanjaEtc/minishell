#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    char *line;
    t_env *env;
    
    (void)ac; (void)av;
    ft_putstr_fd("Welcome to minishell!\n", 1);
    env = env_set(envp);
    if (!env)
    {
        perror("Error: Failed to initialize environment variables.\n");
        return (1);
    }
    while (1)
    {
        setup_signals();
        line = readline("minishell> ");
        if (!line)
            break;
        if (line && *line)
            add_history(line);
        if (unclosed_quote(line))//sers simplement a gerer le cas des quotes non fermees
        {
            perror("Error: unclosed quote\n");
            free(line);
        }
        //else
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
