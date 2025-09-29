/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:24 by gkankia           #+#    #+#             */
/*   Updated: 2025/09/29 16:29:29 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_redirection(t_minishell *sh, char *redir, char *file)
{
	if (ft_strcmp(redir, "<") == 0)
	{
		sh->in_fd = open(file, O_RDONLY);
		if (sh->in_fd < 0)
			return (1);
	}
	else if (ft_strcmp(redir, ">") == 0)
	{
		sh->out_fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (sh->out_fd < 0)
			return (1);
	}
	else if (ft_strcmp(redir, ">>") == 0)
	{
		sh->out_fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (sh->out_fd < 0)
			return (1);
	}
	else if (ft_strcmp(redir, "<<") == 0)
	{
		sh->in_fd = here_doc(file);
		if (sh->in_fd < 0)
			return (1);
	}
	return (0);
}

int	handle_single_redir(t_minishell *sh, char *redir, char *file)
{
	if (ft_strcmp(redir, "<") == 0 || ft_strcmp(redir, "<<") == 0)
	{
		if (sh->in_fd != STDIN_FILENO)
			close(sh->in_fd);
	}
	else
	{
		if (sh->out_fd != STDOUT_FILENO)
			close(sh->out_fd);
	}
	if (process_redirection(sh, redir, file))
	{
		perror(file);
		free_minishell(sh);
		exit (1);
	}
	return (0);
}

int	handle_redirections(t_minishell *sh, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if ((is_redirections(sh, i) && i + 1 < end && \
is_redirections(sh, i + 1)))
		{
			sh->exit_code = 2;
			return (1);
		}
		if (is_redirections(sh, i) && i + 1 < end)
		{
			if (handle_single_redir(sh, sh->args[i], sh->args[i + 1]))
			{
				sh->exit_code = 1;
				return (1);
			}
			i += 2;
		}
		else
			i++;
	}
	return (0);
}

void	wait_for_children(t_minishell *sh)
{
	int		status;
	pid_t	wpid;
	int		sig;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT && wpid == sh->last_pid)
				write(2, "Quit (core dumped)\n", 19);
			else if (sig == SIGINT && wpid == sh->last_pid)
				write(1, "\n", 1);
			if (wpid == sh->last_pid)
				sh->exit_code = 128 + sig;
		}
		else if (WIFEXITED(status) && wpid == sh->last_pid)
			sh->exit_code = WEXITSTATUS(status);
		wpid = wait(&status);
	}
}

void	execute_command(t_minishell *sh)
{
	int	i;
	int	start;
	int	prev_fd;

	if (!sh->args || !sh->args[0])
		return ;
	i = 0;
	prev_fd = -1;
	while (sh->args[i])
	{
		start = i;
		check_no_command_redirection(sh, start);
		while (sh->args[i] && ft_strcmp(sh->args[i], "|") != 0)
			i++;
		update_fds(sh, &prev_fd);
		exec_subcmd(sh, start, i, &prev_fd);
		if (sh->args[i] && ft_strcmp(sh->args[i], "|") == 0)
			i++;
	}
	wait_for_children(sh);
}
