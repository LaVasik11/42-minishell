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
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			ms->exit_code = WEXITSTATUS(status);
	}
}

void	execute_command(t_minishell *ms)
{
	int	i;
	int	start;
	int	prev_fd;

	if (!check_infiles(ms->args, ms))
		return ;
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
		handle_redirections(ms, start, i);
		exec_subcmd(ms, start, i, &prev_fd);
		if (ms->args[i] && ft_strcmp(ms->args[i], "|") == 0)
			i++;
	}
	wait_for_children(ms);
}
