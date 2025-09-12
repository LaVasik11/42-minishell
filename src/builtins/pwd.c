/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgy-kankiya <georgy-kankiya@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:29:19 by tmkrtumy          #+#    #+#             */
/*   Updated: 2025/09/12 14:12:11 by georgy-kank      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_working_directory(t_minishell *sh)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_putendl_fd(get_env_value(sh->envp, "PWD"), sh->out_fd);
	ft_putendl_fd(path, sh->out_fd);
	free(path);
	return (1);
}
