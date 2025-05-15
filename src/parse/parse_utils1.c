#include "minishell.h"

int	skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int	find_closing_quote(char *line, int i, char quote)
{
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		return (i);
	return (-1);
}

void	free_all(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_special(char c)
{
	return (c == ' ' || c == '\t' || c == '\0');
}
