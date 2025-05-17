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

static void	child_process_logic(t_minishell *sh)
{
	char	*path;

	path = find_in_path(sh->args[0]);
	if (!path)
		exit_with_error(sh, "minishell");
	execve(path, sh->args, sh->envp);
	free(path);
	exit_with_error(sh, "minishell");
}

void	execute_command(t_minishell *sh)
{
	pid_t	pid;
	int		status;

	if (!sh->args || !sh->args[0])
		return ;
	pid = fork();
	if (pid == -1)
		exit_with_error(sh, "fork");
	else if (pid == 0)
		child_process_logic(sh);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->exit_code = WEXITSTATUS(status);
	else
		sh->exit_code = 1;
}
