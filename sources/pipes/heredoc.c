#include "../../includes/minishell.h"

static char	*write_heredoc_to_temp(char *limiter, int count)
{
	char	*filename;
	char	*count_str;
	char	*line;
	int		fd;

	// 1. Génération d'un nom de fichier unique propre (ex: /tmp/.ms_hd_1)
	count_str = ft_itoa(count); // Remplace par ton ft_itoa
	filename = ft_strjoin("/tmp/.minishell_hd_", count_str); // Remplace par ton ft_strjoin
	free(count_str);

	// 2. Ouverture du fichier temporaire en écriture
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(filename);
		return (NULL);
	}

	// 3. Boucle de lecture readline
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0) // Remplace par ton ft_strcmp
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd); // Écrit la ligne + un '\n' dans le fichier
		free(line);
	}
	close(fd);
	return (filename); // On retourne le chemin pour le donner au token
}

/*
** Parcourt tes commandes et pré-traite tous les HEREDOC avant l'exécution.
*/
void	exec_all_heredocs(t_cmd *cmds)
{
	t_cmd		*curr_cmd;
	t_token		*curr_redir;
	char		*temp_file;
	static int	hd_counter = 0;

	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redirs;
		while (curr_redir)
		{
			if (curr_redir->type == HEREDOC)
			{
				// On écrit le heredoc et on récupère le chemin du fichier temporaire
				temp_file = write_heredoc_to_temp(curr_redir->value, hd_counter++);
				
				if (temp_file)
				{
					// On libère le limiteur (ex: "EOF") qui ne nous sert plus
					free(curr_redir->value);
					
					// Transformation magique du token
					curr_redir->value = temp_file; // Le fichier devient la cible
					curr_redir->type = RED_IN;     // Le HEREDOC devient un simple '<'
				}
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
}

void	unlink_temporary_heredocs(t_cmd *cmds)
{
	t_cmd	*curr_cmd = cmds;
	t_token	*curr_redir;

	while (curr_cmd)
	{
		curr_redir = curr_cmd->redirs;
		while (curr_redir)
		{
			// Grâce à notre transformation, les anciens heredocs sont de type RED_IN 
			// et commencent par "/tmp/.minishell_hd_"
			if (curr_redir->type == RED_IN && 
				ft_strncmp(curr_redir->value, "/tmp/.minishell_hd_", 19) == 0)
			{
				unlink(curr_redir->value); // Supprime le fichier physique du disque
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
}

static char	*read_heredoc_line(void)
{
	char	buf[2];
	char	*line;
	char	*temp;
	int		bytes;

	if (isatty(STDIN_FILENO))
		return (readline("> "));
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		bytes = read(STDIN_FILENO, buf, 1);
		if (bytes <= 0)
			break ;
		buf[1] = '\0';
		if (buf[0] == '\n')
			break ;
		temp = ft_strjoin_three(line, buf, "");
		free(line);
		line = temp;
	}
	if (bytes <= 0 && ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

int	handle_heredoc(char *limiter)
{
	char	*line;
	int		pipe_fd[2];
	
	if (pipe(pipe_fd) == -1)
		return (-1);
	while (1)
	{
		line = read_heredoc_line();
		if (!line)
			break;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}