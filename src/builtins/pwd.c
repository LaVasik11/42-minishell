/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:29:19 by tmkrtumy          #+#    #+#             */
/*   Updated: 2025/09/15 15:11:34 by gkankia          ###   ########.fr       */
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
