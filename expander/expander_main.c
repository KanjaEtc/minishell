#include "expand.h"
#include "../env/env.h"
#include "../libft_stripped/libft_stripped.h"

int	is_valid_var_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	var_len(char *str)
{
	int	i;

	if (str[0] == '?')
		return (1);
	i = 0;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	return (i);
}

char	*handle_dollar(char *str, int i, t_env *env)
{
	char	*var_name;
	char	*before;
	char	*after;
	char	*new_s;

    printf("start of the test\n");
	var_name = ft_substr(str, i + 1, var_len(&str[i + 1]));
    printf("var_name: %s\n", var_name);
	before = ft_substr(str, 0, i);
    printf("before: %s\n", before);
	after = ft_substr(str, i + 1 + ft_strlen(var_name), ft_strlen(str));
    printf("after: %s\n", after);
	new_s = ft_strjoin_three(before, ft_get_env(var_name, env), after);
    printf("new_s: %s\n", new_s);
	free(before);
	free(after);
	free(var_name);
    free(str);
    printf("end of the test\n");
	return (new_s);
}

int main(int ac, char **av, char **envp)
{
    (void)ac; (void)av;
    if (!envp || envp[0] == NULL)
        return (1); 
    t_env *env = init_env(envp);
    printf("--------------------\n");
    printf("Expanded string: %s\n", handle_dollar("Hello $USER , this is $SHLVL ", 6, env));
    free_env(env);
    printf("--------------------\n");
    return (0);
}
