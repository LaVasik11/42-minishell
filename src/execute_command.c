#include "minishell.h"

void	execute_command(t_minishell *sh)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!sh->args || !sh->args[0])
		return ;
	pid = fork();
	if (pid == -1)
		exit_with_error(sh, "fork");
	else if (pid == 0)
	{
		path = find_in_path(sh->args[0]);
		if (!path)
			exit_with_error(sh, "minishell");
		execve(path, sh->args, sh->envp);
		perror("minishell");
		free(path);
		free_minishell(sh);
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
}
