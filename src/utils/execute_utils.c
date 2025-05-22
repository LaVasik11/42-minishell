#include "minishell.h"

int	here_doc(const char *delimiter)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}

int	has_pipe(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		if (ft_strcmp(args[i++], "|") == 0)
			return (1);
	return (0);
}

int	execute_builtin(t_minishell *ms)
{
	if (!ms->args || !ms->args[0])
		return (0);
	if (ft_strcmp(ms->args[0], "cd") == 0)
		return (change_directory(ms));
	else if (ft_strcmp(ms->args[0], "exit") == 0)
		return (builtin_exit(ms));
	else if (ft_strcmp(ms->args[0], "env") == 0)
		return (builtin_env(ms));
	else if (ft_strcmp(ms->args[0], "export") == 0)
		return (builtin_export(ms));
	else if (ft_strcmp(ms->args[0], "unset") == 0)
		return (builtin_unset(ms));
	return (0);
}
