#include "minishell.h"

// Une petite fonction pour afficher le type sous forme de texte lisible
void	print_token_type(t_type type)
{
	if (type == WORD) printf("WORD");
	else if (type == PIPE) printf("PIPE");
	else if (type == RED_IN) printf("RED_IN");
	else if (type == RED_OUT) printf("RED_OUT");
	else if (type == HEREDOC) printf("HERE_DOC"); // Ajuste selon le nom dans ton enum
	else if (type == APPEND) printf("APPEND");
}

int	main(int ac, char **av)
{
	t_token	*tokens;
	t_token	*tmp;

	if (ac != 2)
	{
		printf("Usage: ./test_lexer \"ta commande a tester\"\n");
		return (1);
	}
	printf("Ligne brute : %s\n\n", av[1]);
	
	// 1. Lancement de ton lexer
	tokens = lexer(av[1]);
	
	// 2. Lancement de ton assignation de types
	assign_token_types(tokens);

	// 3. Affichage des résultats
	tmp = tokens;
	while (tmp)
	{
		printf("Token : [%s] \t-> Type : ", tmp->value);
		print_token_type(tmp->type);
		printf("\n");
		tmp = tmp->next;
	}

	// 4. Nettoyage de la mémoire (si tu as codé ft_free_tokens)
	// ft_free_tokens(&tokens);
	return (0);
}