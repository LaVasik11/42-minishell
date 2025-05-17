/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:32 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/16 17:55:33 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_minishell *sh)
{
	sh->line = NULL;
	sh->args = NULL;
	sh->prompt = NULL;
	sh->envp = NULL;
	sh->path_dirs = NULL;
	sh->pipe_fds = NULL;
	sh->pipe_count = 0;
	sh->in_fd = 0;
	sh->out_fd = 1;
	sh->last_exit_code = 0;
	sh->is_running = 1;
	sh->exit_code = 0;
}
