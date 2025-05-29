/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:28 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/28 17:03:20 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_minishell(t_minishell *shell)
{
	if (!shell)
		return ;
	free(shell->line);
	shell->line = NULL;
	free(shell->prompt);
	shell->prompt = NULL;
	free_array(shell->args);
	shell->args = NULL;
	free_array(shell->envp);
	shell->envp = NULL;
	shell->in_fd = 0;
	shell->out_fd = 1;
	shell->exit_code = 0;
}
