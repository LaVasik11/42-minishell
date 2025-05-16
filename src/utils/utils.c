/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:21 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/16 17:55:22 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_error(t_minishell *sh, const char *msg)
{
	perror(msg);
	free_minishell(sh);
	exit(1);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
}

char	*join_path(char *dir, char *cmd)
{
	char	*path;
	size_t	len;

	len = strlen(dir) + strlen(cmd) + 2;
	path = malloc(len);
	if (!path)
		return (NULL);
	strcpy(path, dir);
	strcat(path, "/");
	strcat(path, cmd);
	return (path);
}
