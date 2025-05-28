/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:42:19 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/28 16:42:20 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_infiles(char **args, t_minishell *sh)
{
	int		i;
	int		fd;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<") == 0 && args[i + 1])
		{
			fd = open(args[i + 1], O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(args[i + 1]);
				sh->exit_code = 1;
				return (0);
			}
			close(fd);
			i++;
		}
		i++;
	}
	return (1);
}
