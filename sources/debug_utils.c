#include "../../includes/minishell.h"
#include "../../includes/debug_utils.h"

void print_env(t_env *env)
{
    t_env *current;
	
	current = env;
	while (current)
	{
		printf("%s = %s\n", current->key, current->value);
		current = current->next;
	}
}

void print_tokens(t_token *tokens)
{
    t_token *current;
    
    current = tokens;
    while (current)
    {
        printf("Token: %s, Type: %d\n", current->val, current->type);
        current = current->next;
    }
}