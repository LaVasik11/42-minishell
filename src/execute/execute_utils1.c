/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:26:48 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/24 14:28:04 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(const char *delimiter)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}

int	has_pipe(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		if (ft_strcmp(args[i++], "|") == 0)
			return (1);
	return (0);
}

int	execute_builtin(t_minishell *ms)
{
	if (!ms->args || !ms->args[0])
		return (0);
	if (ft_strcmp(ms->args[0], "cd") == 0)
		return (change_directory(ms));
	else if (ft_strcmp(ms->args[0], "exit") == 0)
		return (builtin_exit(ms));
	else if (ft_strcmp(ms->args[0], "env") == 0)
		return (builtin_env(ms));
	else if (ft_strcmp(ms->args[0], "export") == 0)
		return (builtin_export(ms));
	else if (ft_strcmp(ms->args[0], "unset") == 0)
		return (builtin_unset(ms));
	return (0);
}

void	handle_child_fds(t_minishell *ms, int pipe_fd[2], int has_pipe)
{
	if (ms->in_fd != STDIN_FILENO)
	{
		dup2(ms->in_fd, STDIN_FILENO);
		close(ms->in_fd);
	}
	if (ms->out_fd != STDOUT_FILENO)
	{
		dup2(ms->out_fd, STDOUT_FILENO);
		close(ms->out_fd);
	}
	if (has_pipe)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	handle_parent_fds(t_minishell *ms, int pipe_fd[2],\
	int has_pipe, int *prev_fd)
{
	if (ms->in_fd != STDIN_FILENO)
		close(ms->in_fd);
	if (ms->out_fd != STDOUT_FILENO)
		close(ms->out_fd);
	if (has_pipe)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}
