#include "minishell.h"

char	*copy_unquoted_segment(char *line, int *i)
{
	char	*segment;
	int		start;

	start = *i;
	while (line[*i] && !is_special(line[*i]) && !is_quote(line[*i])
		&& line[*i] != '$')
		(*i)++;
	segment = copy_segment(line, start, *i);
	return (segment);
}

char	*copy_unquoted_arg(char *line, int *i)
{
	char	*result;
	char	*segment;
	char	*var;

	result = NULL;
	while (line[*i] && !is_special(line[*i]) && !is_quote(line[*i]))
	{
		if (line[*i] == '$')
		{
			var = parse_dollar(line, i);
			if (!var)
				return (free(result), NULL);
			result = str_join_free(result, var);
		}
		else
		{
			segment = copy_unquoted_segment(line, i);
			if (!segment)
				return (free(result), NULL);
			result = str_join_free(result, segment);
		}
	}
	return (result);
}
