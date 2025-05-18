// src/builtins/export.c

#include "minishell.h"

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

static int	env_key_match(char *env_entry, char *arg, size_t len)
{
	return (ft_strncmp(env_entry, arg, len) == 0 && env_entry[len] == '=');
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
		if (env_key_match(sh->envp[i], arg, len))
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
			if (ft_strchr(sh->args[i], '='))
				add_or_update_env(sh, sh->args[i]);
			i++;
		}
	}
	sh->exit_code = 0;
	return (1);
}
