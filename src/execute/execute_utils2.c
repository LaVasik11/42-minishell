/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:03 by gkankia           #+#    #+#             */
/*   Updated: 2025/06/13 19:19:01 by gkankia          ###   ########.fr       */
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

void	validate_exec_args(t_minishell *ms, char *path)
{
	struct stat	st;

	if (ft_strcmp(ms->args[0], "cd") == 0 && ms->args[2])
		exit_with_error(ms, " too many arguments", 1);
	if (ft_strcmp(ms->args[0], "cd") == 0 && (!path || *path == '\0'))
		exit_with_error(ms, " No such file or directory", 1);
	if (!path || *path == '\0')
		exit_with_error(ms, " command not found", 127);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		exit_with_error(ms, " Is a directory", 126);
	if (access(path, F_OK) != 0)
		exit_with_error(ms, " No such file or directory", 127);
	if (access(path, X_OK) != 0)
		exit_with_error(ms, " Permission denied", 126);
}

void	child_process(t_minishell *ms, t_subprocess_data *data)
{
	char	*path;

	signal(SIGPIPE, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	handle_child_fds(ms, data->pipe_fd, data->has_pipe);
	if (data->redir_error)
		exit(1);
	path = find_in_path(ms, data->cmd[0]);
	validate_exec_args(ms, path);
	if (!path)
		exit_with_error(ms, " No such file or directory", 1);
	execve(path, data->cmd, ms->envp);
	free(path);
	exit_with_error(ms, "execve", 1);
}

void	exec_subcmd(t_minishell *ms, int start, int end, int *prev_fd)
{
	pid_t				pid;
	t_subprocess_data	data;

	data.cmd = build_argv(ms->args, start, end);
	data.has_pipe = (ms->args[end] && ft_strcmp(ms->args[end], "|") == 0);
	if (data.has_pipe && pipe(data.pipe_fd) == -1)
		exit_with_error(ms, "pipe", 1);
	pid = fork();
	if (pid == 0)
	{
		data.redir_error = handle_redirections(ms, start, end);
		child_process(ms, &data);
	}
	ms->last_pid = pid;
	handle_parent_fds(ms, data.pipe_fd, data.has_pipe, prev_fd);
	free_args(data.cmd);
	if (ms->in_fd != STDIN_FILENO)
		close(ms->in_fd);
	if (ms->out_fd != STDOUT_FILENO)
		close(ms->out_fd);
}
