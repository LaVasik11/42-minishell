/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgy-kankiya <georgy-kankiya@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:24 by gkankia           #+#    #+#             */
/*   Updated: 2025/09/12 11:50:04 by georgy-kank      ###   ########.fr       */
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

int	handle_redirections(t_minishell *sh, int start, int end)
{
	int		i;
	int		err;

	err = 0;
	i = start;
	while (i < end)
	{
		if ((ft_strcmp(sh->args[i], "<") == 0
				|| ft_strcmp(sh->args[i], ">") == 0
				|| ft_strcmp(sh->args[i], ">>") == 0
				|| ft_strcmp(sh->args[i], "<<") == 0) && i + 1 < end)
		{
			if (process_redirection(sh, sh->args[i], sh->args[i + 1]))
				err = 1;
			i += 2;
		}
		else
			i++;
	}
	return (err);
}

void	update_fds(t_minishell *sh, int *prev_fd)
{
	if (*prev_fd < 0)
		sh->in_fd = STDIN_FILENO;
	else
		sh->in_fd = *prev_fd;
	sh->out_fd = STDOUT_FILENO;
}

void	wait_for_children(t_minishell *sh)
{
	int		status;
	pid_t	wpid;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == sh->last_pid)
		{
			if (WIFEXITED(status))
				sh->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				sh->exit_code = 128 + WTERMSIG(status);
		}
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
		while (sh->args[i] && ft_strcmp(sh->args[i], "|") != 0)
			i++;
		update_fds(sh, &prev_fd);
		exec_subcmd(sh, start, i, &prev_fd);
		if (sh->args[i] && ft_strcmp(sh->args[i], "|") == 0)
			i++;
	}
	wait_for_children(sh);
}
