#include "minishell.h"

static int	skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static char	*copy_word(char *line, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = line[start++];
	word[i] = '\0';
	return (word);
}

char	**parse_input(char *line)
{
	char	**args;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	args = malloc(sizeof(char *) * 1024);
	if (!args)
		return (NULL);
	while (line[i])
	{
		i = skip_spaces(line, i);
		if (!line[i])
			break ;
		j = i;
		while (line[i] && line[i] != ' ' && line[i] != '\t')
			i++;
		args[k] = copy_word(line, j, i);
		if (!args[k])
			return (NULL);
		k++;
	}
	args[k] = NULL;
	return (args);
}
