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

int	execute_builtin(t_minishell *ms)
{
	if (!ms->args || !ms->args[0])
		return (0);
	if (ft_strcmp(ms->args[0], "cd") == 0)
		return (change_directory(ms));
	// else if (ft_strcmp(ms->args[0], "exit") == 0)
	// 	return (builtin_exit(ms));
	return (0);
}

static void	child_process_logic(t_minishell *ms)
{
	char	*path;

	path = find_in_path(ms->args[0]);
	if (!path)
		exit_with_error(ms, "minishell");
	execve(path, ms->args, ms->envp);
	free(path);
	exit_with_error(ms, "minishell");
}

void	execute_command(t_minishell *ms)
{
	pid_t	pid;
	int		status;

	if (!ms->args || !ms->args[0])
		return ;
	if (execute_builtin(ms))
		return ;
	pid = fork();
	if (pid == -1)
		exit_with_error(ms, "fork");
	else if (pid == 0)
		child_process_logic(ms);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms->exit_code = WEXITSTATUS(status);
	else
		ms->exit_code = 1;
}
