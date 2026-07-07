#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac; (void)av;
    // char *line;
    t_env *env;
    
    
    ft_putstr_fd("Welcome to minishell!\n", 1);
    env = env_set(envp);
    printf("Environment setup complete.\n");
    printf("---------------------------------\n");
    if (!env)
    {
        ft_putstr_fd("Error: Failed to initialize environment variables.\n", 2);
        return (1);
    }
    print_env(env);
    // while (1)
    // {
    //     line = readline("minishell> ");
    //     if (!line)
    //         break;
    //     if (line && *line)
    //         add_history(line);
    //     if (unclosed_quote(line))//sers simplement a gerer le cas des quotes non fermees
    //     {
    //         perror("Error: unclosed quote\n");
    //         free(line);
    //     }
    //     //else
    //     // {
    //     //     t_token *tokens = lexer(line);
    //     //     //suite sera coder plus tard
    //     // }
    // }
    // rl_clear_history();
    printf("---------------------------------\n");
    printf("Exiting minishell. Cleaning up...\n");
    free_env(env);
    return 0;
}

// Sources :
// "https://man7.org/linux/man-pages/man3/readline.3.html"
// "https://i.sstatic.net/lVx5P.gif"
// "https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions"
