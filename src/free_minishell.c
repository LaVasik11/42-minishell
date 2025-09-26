/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgy-kankiya <georgy-kankiya@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:28 by gkankia           #+#    #+#             */
/*   Updated: 2025/09/26 12:32:05 by georgy-kank      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_temp_data(t_minishell *sh)
{
	free_args(sh->args);
	sh->args = NULL;
	free(sh->line);
	sh->line = NULL;
	sh->is_two_operator = 0;
}

void	free_minishell(t_minishell *sh)
{
	if (!sh)
		return ;
	free(sh->path);
	sh->path = NULL;
	free(sh->line);
	sh->line = NULL;
	free_array(sh->args);
	sh->args = NULL;
	free_array(sh->envp);
	sh->envp = NULL;
	if (sh->data)
	{
		free_array(sh->data->cmd);
		sh->data->cmd = NULL;
	}
	sh->in_fd = 0;
	sh->out_fd = 1;
}
