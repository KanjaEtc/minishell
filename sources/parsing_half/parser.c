#include "parser.h"

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;
	t_token	*curr;

	if (!tokens)
		return (NULL);
	cmd_list = NULL;
	curr = tokens;
	while (curr)
	{
		new_cmd = lst_new_cmd();
		new_cmd = get_cmd_args(curr);
		if (curr)
			curr = curr->next;
	}
	return (cmd_list);
}

// t_cmd   *parse_tokens(t_token *tokens)
// {
//     t_cmd   *cmd_list;
//     t_cmd   *new_cmd;
//     t_token *curr;

//     if (!tokens)
//         return (NULL);
//     cmd_list = NULL;
//     curr = tokens;
//     while (curr)
//     {
//         new_cmd = lst_new_cmd();
//         if (!new_cmd)
//             return (NULL); // Sécurité malloc
        
//         // 1. On remplit les arguments (Correction ici !)
//         new_cmd->args = get_cmd_args(curr);
        
//         // 2. Sous-boucle pour remplir les redirections du maillon actuel
//         while (curr && curr->type != PIPE)
//         {
//             if (curr->type == RED_IN || curr->type == RED_OUT
//                 || curr->type == APPEND || curr->type == HEREDOC)
//             {
//                 add_redir_node(&new_cmd->redirs, curr);
//                 if (curr->next)
//                     curr = curr->next; // On saute le fichier puisqu'il est géré
//             }
//             curr = curr->next;
//         }
        
//         // 3. ICI : Il faudra ajouter `new_cmd` à ta liste principale `cmd_list`
//         // 4. ICI : Si curr est un PIPE, il faut passer au token suivant pour la prochaine commande
//     }
//     return (cmd_list);
// }