/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgy-kankiya <georgy-kankiya@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:03 by gkankia           #+#    #+#             */
/*   Updated: 2025/09/22 11:53:56 by georgy-kank      ###   ########.fr       */
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

void	validate_exec_args(t_minishell *sh, char *path, int start, int end)
{
	struct stat	st;

	if (ft_strcmp(sh->args[start], "cd") == 0 && end - start > 2)
		exit_with_error(sh, "Too many arguments", 1, 0);
	if (ft_strcmp(sh->args[start], "cd") == 0 && (!path || *path == '\0'))
		exit_with_error(sh, "No such file or directory", 1, 0);
	if (!path || *path == '\0')
		exit_with_error(sh, "Command not found", 127, start);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		exit_with_error(sh, "Is a directory", 126, 0);
	if (access(path, F_OK) != 0)
		exit_with_error(sh, "No such file or directory", 127, 0);
	if (access(path, X_OK) != 0)
		exit_with_error(sh, "Permission denied", 126, 0);
}

void	child_process(t_minishell *sh, t_subprocess_data *data, \
int start, int end)
{
	char	*path;

	signal(SIGPIPE, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	handle_child_fds(sh, data->pipe_fd, data->has_pipe);
	if (data->redir_error)
		exit(1);
	if (is_builtin_cmd(data->cmd[0]))
	{
		free_args(sh->args);
		sh->args = data->cmd;
		if (execute_builtin(sh))
			exit(sh->exit_code);
		free_minishell(sh);
		exit(0);
	}
	path = find_in_path(sh, data->cmd[0]);
	validate_exec_args(sh, path, start, end);
	if (!path)
		exit_with_error(sh, "No such file or directory", 127, 0);
	free_args(sh->args);
	execve(path, data->cmd, sh->envp);
	free(path);
	exit_with_error(sh, "execve", 1, 0);
}

void	fork_and_exec_child(t_minishell *sh, \
t_subprocess_data *data, int start, int end)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_with_error(sh, "fork", 1, 0);
	if (pid == 0)
	{
		data->redir_error = handle_redirections(sh, start, end);
		child_process(sh, data, start, end);
	}
	sh->last_pid = pid;
}

void	exec_subcmd(t_minishell *sh, int start, int end, int *prev_fd)
{
	t_subprocess_data	data;

	data.cmd = build_argv(sh->args, start, end);
	if (!data.cmd || !data.cmd[0])
	{
		free_args(data.cmd);
		check_no_command_redirection(sh);
		return ;
	}
	data.has_pipe = (sh->args[end] && ft_strcmp(sh->args[end], "|") == 0);
	if (is_builtin_cmd(data.cmd[0]) && !data.has_pipe)
	{
		execute_builtin_in_parent(sh, start, end);
		free_args(data.cmd);
		return ;
	}
	if (data.has_pipe && pipe(data.pipe_fd) == -1)
	{
		free_args(data.cmd);
		exit_with_error(sh, "pipe", 1, 0);
	}
	fork_and_exec_child(sh, &data, start, end);
	handle_parent_fds(sh, data.pipe_fd, data.has_pipe, prev_fd);
	free_args(data.cmd);
}
