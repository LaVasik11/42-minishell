#include "minishell.h"

int	handle_infile(t_minishell *sh, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	sh->in_fd = fd;
	return (0);
}

int	handle_outfile_trunc(t_minishell *sh, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (1);
	sh->out_fd = fd;
	return (0);
}

int	handle_outfile_append(t_minishell *sh, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
		return (1);
	sh->out_fd = fd;
	return (0);
}

int	handle_heredoc(t_minishell *sh, char *delimiter)
{
	int	fd;

	fd = here_doc(delimiter);
	if (fd < 0)
		return (1);
	sh->in_fd = fd;
	return (0);
}

int	process_redirection(t_minishell *sh, char *redir, char *file)
{
	if (ft_strcmp(redir, "<") == 0)
		return (handle_infile(sh, file));
	else if (ft_strcmp(redir, ">") == 0)
		return (handle_outfile_trunc(sh, file));
	else if (ft_strcmp(redir, ">>") == 0)
		return (handle_outfile_append(sh, file));
	else if (ft_strcmp(redir, "<<") == 0)
		return (handle_heredoc(sh, file));
	return (0);
}
