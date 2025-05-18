#include "minishell.h"

int	builtin_exit(t_minishell *sh)
{
	write(1, "exit\n", 5);
	free_minishell(sh);
	exit(0);
}
