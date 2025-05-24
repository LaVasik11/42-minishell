/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:20 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/24 14:27:21 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_minishell *sh)
{
	int	i;

	i = 0;
	while (sh->envp && sh->envp[i])
	{
		if (ft_strchr(sh->envp[i], '='))
			printf("%s\n", sh->envp[i]);
		i++;
	}
	sh->exit_code = 0;
	return (1);
}
