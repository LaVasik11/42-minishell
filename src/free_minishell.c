/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgy-kankiya <georgy-kankiya@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:28 by gkankia           #+#    #+#             */
/*   Updated: 2025/09/09 21:25:40 by georgy-kank      ###   ########.fr       */
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

void	free_minishell(t_minishell *sh)
{
	if (!sh)
		return ;
	free(sh->line);
	sh->line = NULL;
	free_array(sh->args);
	sh->args = NULL;
	free_array(sh->envp);
	sh->envp = NULL;
	sh->in_fd = 0;
	sh->out_fd = 1;
}
