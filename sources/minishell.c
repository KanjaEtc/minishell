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
        prompt_signals();
        line = readline("minishell> ");
        if (line && *line)
            add_history(line);
        else
        {
            free(line);
            continue;
        }
        t_token *tokens = lexer(line);
        if (!tokens)
        {
            free(line);
            continue;
        }
        print_tokens(tokens);
        // expand_tokens(tokens, env);
        // free(line);
    }
    rl_clear_history();
    free_env(env);
    return 0;
}

// Sources :
// "https://man7.org/linux/man-pages/man3/readline.3.html"
// "https://i.sstatic.net/lVx5P.gif"
// "https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions"
