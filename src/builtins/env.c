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
