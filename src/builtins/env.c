/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgy-kankiya <georgy-kankiya@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:20 by gkankia           #+#    #+#             */
/*   Updated: 2025/09/12 13:21:26 by georgy-kank      ###   ########.fr       */
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

char	**add_env_entry(char **envp, char *new_entry)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp && envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (envp);
	i = 0;
	while (envp && envp[i])
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i++] = new_entry;
	new_env[i] = NULL;
	free(envp);
	return (new_env);
}
