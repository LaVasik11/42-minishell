/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:26:36 by gkankia           #+#    #+#             */
/*   Updated: 2025/06/13 17:14:01 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_part(t_minishell *sh, char *cwd)
{
	char	*home;
	char	*path_part;

	home = get_env_value(sh->envp, "HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		path_part = ft_strjoin("~", cwd + ft_strlen(home));
		free(home);
		if (!path_part)
			return (NULL);
	}
	else
	{
		free(home);
		path_part = ft_strdup(cwd);
		if (!path_part)
			return (NULL);
	}
	return (path_part);
}

char	*build_prompt(char *user, char *path)
{
	char	*tmp;
	char	*prompt;
	char	*final;

	tmp = ft_strjoin(user, ":");
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin(tmp, path);
	free(tmp);
	if (!prompt)
		return (NULL);
	final = ft_strjoin(prompt, "$ ");
	free(prompt);
	return (final);
}

char	*get_prompt(t_minishell *sh)
{
	char	cwd[PATH_MAX];
	char	*user;
	char	*path;
	char	*prompt;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup("minishell$ "));
	path = get_path_part(sh, cwd);
	if (!path)
		return (ft_strdup("minishell$ "));
	user = get_env_value(sh->envp, "USER");
	if (!user)
		user = "user";
	prompt = build_prompt(user, path);
	free(path);
	free(user);
	if (!prompt)
		return (ft_strdup("minishell$ "));
	return (prompt);
}
