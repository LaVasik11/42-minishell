/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:24 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/16 18:43:14 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_redirection(t_minishell *ms, char *redir, char *file)
{
	if (ft_strcmp(redir, "<") == 0)
	{
		ms->in_fd = open(file, O_RDONLY);
		if (ms->in_fd < 0)
			return (1);
	}
	else if (ft_strcmp(redir, ">") == 0)
	{
		ms->out_fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (ms->out_fd < 0)
			return (1);
	}
	else if (ft_strcmp(redir, ">>") == 0)
	{
		ms->out_fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (ms->out_fd < 0)
			return (1);
	}
	else if (ft_strcmp(redir, "<<") == 0)
	{
		ms->in_fd = here_doc(file);
		if (ms->in_fd < 0)
			return (1);
	}
	return (0);
}

int	handle_redirections(t_minishell *ms, int start, int end)
{
	int		i;
	int		err;

	err = 0;
	i = start;
	while (i < end)
	{
		if ((ft_strcmp(ms->args[i], "<") == 0 \
			|| ft_strcmp(ms->args[i], ">") == 0 \
			|| ft_strcmp(ms->args[i], ">>") == 0 \
			|| ft_strcmp(ms->args[i], "<<") == 0) && i + 1 < end)
		{
			if (process_redirection(ms, ms->args[i], ms->args[i + 1]))
				err = 1;
			i += 2;
		}
		else
			i++;
	}
	return (err);
}

void	update_fds(t_minishell *ms, int *prev_fd)
{
	if (*prev_fd < 0)
		ms->in_fd = STDIN_FILENO;
	else
		ms->in_fd = *prev_fd;
	ms->out_fd = STDOUT_FILENO;
}

void	wait_for_children(t_minishell *ms)
{
	int		status;
	pid_t	wpid;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == ms->last_pid)
		{
			if (WIFEXITED(status))
				ms->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ms->exit_code = 128 + WTERMSIG(status);
		}
		wpid = wait(&status);
	}
}

void	execute_command(t_minishell *ms)
{
	int	i;
	int	start;
	int	prev_fd;

	if (!ms->args || !ms->args[0])
		return ;
	if (!has_pipe(ms->args) && execute_builtin(ms))
		return ;
	i = 0;
	prev_fd = -1;
	while (ms->args[i])
	{
		start = i;
		while (ms->args[i] && ft_strcmp(ms->args[i], "|") != 0)
			i++;
		update_fds(ms, &prev_fd);
		exec_subcmd(ms, start, i, &prev_fd);
		if (ms->args[i] && ft_strcmp(ms->args[i], "|") == 0)
			i++;
	}
	wait_for_children(ms);
}
