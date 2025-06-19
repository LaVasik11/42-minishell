/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_unquoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:01 by gkankia           #+#    #+#             */
/*   Updated: 2025/06/19 16:53:32 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*copy_unquoted_arg(t_minishell *sh, int *i)
{
	char	*result;
	char	*segment;
	char	*var;

	result = NULL;
	while (sh->line[*i] && !is_special(sh->line[*i]) && !is_quote(sh->line[*i]))
	{
		if (sh->line[*i] == '$')
		{
			var = parse_dollar(sh, i);
			if (!var)
				return (free(result), NULL);
			result = str_join_free(result, var);
		}
		else
		{
			segment = copy_unquoted_segment(sh->line, i);
			if (!segment)
				return (free(result), NULL);
			result = str_join_free(result, segment);
		}
	}
	return (result);
}
