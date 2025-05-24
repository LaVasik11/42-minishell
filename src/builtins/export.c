/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:27:31 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/24 14:27:32 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_line(char *entry)
{
	int	i;

	i = 0;
	while (entry[i] && entry[i] != '=')
		i++;
	printf("declare -x ");
	if (i > 0)
		printf("%.*s", i, entry);
	if (entry[i] == '=')
		printf("=\"%s\"", entry + i + 1);
	printf("\n");
}

static char	**add_env_entry(char **envp, char *new_entry)
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

static void	add_or_update_env(t_minishell *sh, char *arg)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	while (sh->envp && sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], arg, len) == 0 && sh->envp[i][len] == '=')
		{
			free(sh->envp[i]);
			sh->envp[i] = ft_strdup(arg);
			return ;
		}
		i++;
	}
	sh->envp = add_env_entry(sh->envp, ft_strdup(arg));
}

int	builtin_export(t_minishell *sh)
{
	int	i;

	if (!sh->args[1])
	{
		i = 0;
		while (sh->envp && sh->envp[i])
		{
			print_export_line(sh->envp[i]);
			i++;
		}
	}
	else
	{
		i = 1;
		while (sh->args[i])
		{
			if (!is_valid_identifier(sh->args[i]))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(sh->args[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				sh->exit_code = 1;
			}
			else if (ft_strchr(sh->args[i], '='))
			{
				add_or_update_env(sh, sh->args[i]);
			}
			i++;
		}
	}
	if (sh->exit_code == -1)
		sh->exit_code = 0;
	return (1);
}
