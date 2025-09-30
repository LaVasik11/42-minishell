/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgy-kankiya <georgy-kankiya@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:26:48 by gkankia           #+#    #+#             */
/*   Updated: 2025/09/25 17:56:58 by georgy-kank      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *delimiter)
{
	int		fds[2];
	char	*line;

	signal(SIGINT, heredoc_sigint);
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

int	execute_builtin(t_minishell *sh)
{
	if (!sh->args || !sh->args[0])
		return (0);
	if (ft_strcmp(sh->args[0], "cd") == 0)
		return (change_directory(sh));
	else if (ft_strcmp(sh->args[0], "exit") == 0)
		return (builtin_exit(sh));
	else if (ft_strcmp(sh->args[0], "env") == 0)
		return (builtin_env(sh));
	else if (ft_strcmp(sh->args[0], "export") == 0)
		return (builtin_export(sh));
	else if (ft_strcmp(sh->args[0], "unset") == 0)
		return (builtin_unset(sh));
	else if (ft_strcmp(sh->args[0], "echo") == 0)
		return (builtin_echo(sh));
	else if (ft_strcmp(sh->args[0], "pwd") == 0)
		return (print_working_directory(sh));
	return (0);
}

void	handle_child_fds(t_minishell *sh, int pipe_fd[2], int has_pipe)
{
	if (sh->in_fd != STDIN_FILENO)
	{
		if (dup2(sh->in_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(sh->in_fd);
	}
	if (has_pipe)
	{
		close(pipe_fd[0]);
		if (sh->out_fd == STDOUT_FILENO)
		{
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				perror("dup2");
		}
		close(pipe_fd[1]);
	}
	else if (sh->out_fd != STDOUT_FILENO)
	{
		if (dup2(sh->out_fd, STDOUT_FILENO) == -1)
			perror("dup2");
		close(sh->out_fd);
	}
}
