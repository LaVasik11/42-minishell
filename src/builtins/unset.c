/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:35 by gkankia           #+#    #+#             */
/*   Updated: 2025/06/13 18:25:28 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_name(const char *name)
{
	int	i;

	if (!name || !ft_isalpha(name[0]))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_env_var(char ***envp, const char *name)
{
	int	i;
	int	j;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, ft_strlen(name)) == 0
			&& (*envp)[i][ft_strlen(name)] == '=')
		{
			free((*envp)[i]);
			j = i;
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

int	builtin_unset(t_minishell *sh)
{
	int	i;

	i = 1;
	while (sh->args[i])
	{
		if (is_valid_name(sh->args[i]))
			remove_env_var(&sh->envp, sh->args[i]);
		i++;
	}
	sh->exit_code = 0;
	return (1);
}
