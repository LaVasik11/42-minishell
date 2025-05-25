/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_quoted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:54:54 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/16 17:54:55 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_single_quoted(char *line, int *i, int end)
{
	char	*segment;

	segment = copy_segment(line, *i, end);
	*i = end + 1;
	return (segment);
}

char	*process_dollar(t_minishell *ms, int *i, char *result)
{
	char	*var;

	var = parse_dollar(ms, i);
	if (!var)
	{
		free(result);
		return (NULL);
	}
	return (str_join_free(result, var));
}

char	*copy_double_quoted_part(t_minishell *ms, int *i, int end, char *result)
{
	char	*segment;
	int		start;

	while (*i < end)
	{
		if (ms->line[*i] == '$')
		{
			result = process_dollar(ms, i, result);
			if (!result)
				return (NULL);
		}
		else
		{
			start = *i;
			while (*i < end && ms->line[*i] != '$')
				(*i)++;
			segment = copy_segment(ms->line, start, *i);
			if (!segment)
				return (free(result), NULL);
			result = str_join_free(result, segment);
		}
	}
	if (!result)
		return (ft_strdup(""));
	return (result);
}

char	*copy_double_quoted(t_minishell *ms, int *i, int end)
{
	char	*result;

	result = copy_double_quoted_part(ms, i, end, NULL);
	*i = end + 1;
	return (result);
}

char	*copy_quoted_arg(t_minishell *ms, int *i)
{
	char	quote;
	int		end;

	quote = ms->line[*i];
	end = find_closing_quote(ms->line, *i, quote);
	if (end == -1)
		return (NULL);
	*i = *i + 1;
	if (quote == '\'')
		return (copy_single_quoted(ms->line, i, end));
	return (copy_double_quoted(ms, i, end));
}
