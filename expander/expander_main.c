#include "expand.h"
#include "../env/env.h"
#include "../libft_stripped/libft_stripped.h"

// char	*handle_dollar(char *str, int i, t_env *env)
// {
// 	char	*var_name;
// 	char	*before;
// 	char	*after;
// 	char	*new_s;

//     printf("start of the test\n");
// 	var_name = ft_substr(str, i + 1, var_len(&str[i + 1]));
//     printf("var_name: %s\n", var_name);
// 	before = ft_substr(str, 0, i);
//     printf("before: %s\n", before);
// 	after = ft_substr(str, i + 1 + ft_strlen(var_name), ft_strlen(str));
//     printf("after: %s\n", after);
// 	new_s = ft_strjoin_three(before, ft_get_env(var_name, env), after);
//     printf("new_s: %s\n", new_s);
// 	free(before);
// 	free(after);
// 	free(var_name);
//     free(str);
//     printf("end of the test\n");
// 	return (new_s);
// }

// int main(int ac, char **av, char **envp)
// {
//     (void)ac; (void)av; char	*test_str; char	*new_str;
//     if (!envp || envp[0] == NULL)
//         return (1); 
//     t_env *env = init_env(envp);
//     printf("--------------------\n");
// 	test_str = ft_strdup("Hello USER , this is $SHLVL "); //voila ce que j'ai ajoute pour regler le segfault
//     new_str = handle_dollar(test_str, 21, env);
// 	printf("Expanded string: %s\n", new_str);
// 	free(new_str);
//     free_env(env);
//     printf("--------------------\n");
//     return (0);
// }

int main(int ac, char **av, char **envp)
{
    (void)ac; (void)av;
    char    *test_str;
    char    *expanded;

    if (!envp || envp[0] == NULL)
        return (1); 
    t_env *env = init_env(envp);
    
    printf("========================================\n");
    printf("        TEST DE EXPAND_STRING           \n");
    printf("========================================\n\n");

    // CAS 1 : Un dollar classique au milieu de doubles quotes et hors des quotes
    test_str = ft_strdup("Hello \"$USER\" et $SHLVL !");
    printf("1. ORIGINAL : %s\n", test_str);
    expanded = expand_string(test_str, env);
    printf("   EXPANDED : %s\n\n", expanded);
    free(expanded); // expand_string a déjà free(test_str) en interne ou renvoyé le nouveau pointeur

    // CAS 2 : Un dollar à l'intérieur de simples quotes (NE DOIT PAS S'EXPAND)
    // Au lieu de : "L'utilisateur '$USER' n'est pas remplace."
	test_str = ft_strdup("L utilisateur '$USER' n est pas remplace.");
    printf("2. ORIGINAL : %s\n", test_str);
    expanded = expand_string(test_str, env);
    printf("   EXPANDED : %s\n\n", expanded);
    free(expanded);

    // CAS 3 : Un mélange complexe (Simples VS Doubles)
    test_str = ft_strdup("Var stable: '$USER' | Var dynamique: \"$USER\"");
    printf("3. ORIGINAL : %s\n", test_str);
    expanded = expand_string(test_str, env);
    printf("   EXPANDED : %s\n\n", expanded);
    free(expanded);

    // CAS 4 : Variable d'environnement inexistante (Doit disparaître)
    test_str = ft_strdup("Ce dollar $CECI_N_EXISTE_PAS disparait.");
    printf("4. ORIGINAL : %s\n", test_str);
    expanded = expand_string(test_str, env);
    printf("   EXPANDED : %s\n\n", expanded);
    free(expanded);

    // Nettoyage final
    free_env(env);
    printf("========================================\n");
    return (0);
}