/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:28:23 by gkankia           #+#    #+#             */
/*   Updated: 2025/09/15 20:57:44 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_no_command_redirection(t_minishell *sh)
{
	if (!sh->args[1])
		sh->exit_code = 2;
	else if (is_redirections(sh, 0) && is_redirections(sh, 1))
		sh->exit_code = 2;
	else if (ft_strcmp(sh->args[0], "<") == 0)
	{
		sh->exit_code = 1;
		if (access(sh->args[1], F_OK) == 0)
			sh->exit_code = 0;
	}
	else if (ft_strcmp(sh->args[0], ">") == 0 || \
ft_strcmp(sh->args[0], ">>") == 0)
	{
		open(sh->args[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		sh->exit_code = 0;
	}
	else if (ft_strcmp(sh->args[0], "<<") == 0)
		here_doc(sh->args[1]);
}
