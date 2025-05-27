/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:17 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/24 14:27:18 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cd_target(t_minishell *sh, char *oldpwd)
{
	if (!sh->args[1])
		return (getenv("HOME"));
	if (sh->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (NULL);
	}
	if (ft_strcmp(sh->args[1], "-") == 0)
	{
		if (!oldpwd)
		{
			return (NULL);
		}
		write(1, oldpwd, ft_strlen(oldpwd));
		write(1, "\n", 1);
		return (oldpwd);
	}
	return (sh->args[1]);
}

int	change_directory(t_minishell *sh)
{
	static char	*oldpwd = NULL;
	char		*target;
	char		*current_pwd;

	if (sh->args[2])
		exit_with_error(sh, " too many arguments", 1);
	target = get_cd_target(sh, oldpwd);
	if (!target)
		return (sh->exit_code = 1, 0);
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (perror("getcwd"), sh->exit_code = 1, 0);
	if (chdir(target) != 0)
	{
		free(current_pwd);
		sh->exit_code = 1;
		return (0);
	}
	free(oldpwd);
	oldpwd = current_pwd;
	sh->exit_code = 0;
	return (1);
}
