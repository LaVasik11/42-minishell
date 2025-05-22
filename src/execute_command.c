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

char	**build_argv(char **args, int start, int end)
{
	char	**argv;
	int		i;
	int		j;

	argv = malloc(sizeof(char *) * (end - start + 1));
	if (!argv)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
	{
		if (ft_strcmp(args[i], "<") == 0
			|| ft_strcmp(args[i], ">") == 0
			|| ft_strcmp(args[i], ">>") == 0
			|| ft_strcmp(args[i], "<<") == 0)
			i += 2;
		else
			argv[j++] = ft_strdup(args[i++]);
	}
	argv[j] = NULL;
	return (argv);
}

void	handle_redirections(t_minishell *ms, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (ft_strcmp(ms->args[i], "<") == 0 && i + 1 < end)
			ms->in_fd = open(ms->args[i + 1], O_RDONLY);
		else if (ft_strcmp(ms->args[i], ">") == 0 && i + 1 < end)
			ms->out_fd = open(ms->args[i + 1], \
O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (ft_strcmp(ms->args[i], ">>") == 0 && i + 1 < end)
			ms->out_fd = open(ms->args[i + 1], \
O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (ft_strcmp(ms->args[i], "<<") == 0 && i + 1 < end)
			ms->in_fd = here_doc(ms->args[i + 1]);
		if (ft_strcmp(ms->args[i], "<") == 0
			|| ft_strcmp(ms->args[i], ">") == 0
			|| ft_strcmp(ms->args[i], ">>") == 0
			|| ft_strcmp(ms->args[i], "<<") == 0)
			i += 2;
		else
			i++;
	}
}

void	start_subprocess(t_minishell *ms, int start, int end, int *prev_fd)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		has_pipe;
	char	**cmd;
	char	*path;

	cmd = build_argv(ms->args, start, end);
	has_pipe = (ms->args[end] && ft_strcmp(ms->args[end], "|") == 0);
	if (has_pipe && pipe(pipe_fd) == -1)
		exit_with_error(ms, "pipe");
	pid = fork();
	if (pid == 0)
	{
		handle_child_fds(ms, pipe_fd, has_pipe);
		path = find_in_path(cmd[0]);
		if (!path)
			exit_with_error(ms, "minishell: command not found");
		execve(path, cmd, ms->envp);
		free(path);
		exit_with_error(ms, "execve");
	}
	handle_parent_fds(ms, pipe_fd, has_pipe, prev_fd);
}

void	exec_subcmd(t_minishell *ms, int start, int end,
		int *prev_fd)
{
	int	pipe_fd[2];

	start_subprocess(ms, start, end, pipe_fd);
	if (ms->in_fd != STDIN_FILENO)
		close(ms->in_fd);
	if (ms->out_fd != STDOUT_FILENO)
		close(ms->out_fd);
	if (ms->args[ms->pipe_count] && \
		ft_strcmp(ms->args[ms->pipe_count], "|") == 0)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

void	execute_command(t_minishell *ms)
{
	int	i;
	int	prev_fd;
	int	status;
	int	start;

	if (!ms->args || !ms->args[0])
		return ;
	if (!has_pipe(ms->args) && execute_builtin(ms))
		return ;
	prev_fd = -1;
	i = 0;
	while (ms->args[i])
	{
		start = i;
		while (ms->args[i] && ft_strcmp(ms->args[i], "|") != 0)
			i++;
		ms->in_fd = (prev_fd < 0 ? STDIN_FILENO : prev_fd);
		ms->out_fd = STDOUT_FILENO;
		handle_redirections(ms, start, i);
		exec_subcmd(ms, start, i, &prev_fd);
		if (ms->args[i] && ft_strcmp(ms->args[i], "|") == 0)
			i++;
	}
	while (wait(&status) > 0)
		if (WIFEXITED(status))
			ms->exit_code = WEXITSTATUS(status);
}
