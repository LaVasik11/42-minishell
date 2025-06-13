/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:04 by gkankia           #+#    #+#             */
/*   Updated: 2025/06/13 18:52:24 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_operator(t_minishell *ms, int *i)
{
	char	*op;

	if (ms->line[*i] == '<' && ms->line[*i + 1] == '<')
	{
		op = ft_strdup("<<");
		*i += 2;
	}
	else if (ms->line[*i] == '>' && ms->line[*i + 1] == '>')
	{
		op = ft_strdup(">>");
		*i += 2;
	}
	else
	{
		op = malloc(2);
		if (!op)
			return (NULL);
		op[0] = ms->line[*i];
		op[1] = '\0';
		(*i)++;
	}
	return (op);
}

char	*collect_argument(t_minishell *ms, int *i)
{
	char	*arg;
	char	*piece;

	arg = NULL;
	while (ms->line[*i])
	{
		if (is_special(ms->line[*i]))
			break ;
		if (is_quote(ms->line[*i]))
			piece = copy_quoted_arg(ms, i);
		else
			piece = copy_unquoted_arg(ms, i);
		if (!piece)
			return (free(arg), NULL);
		arg = str_join_free(arg, piece);
	}
	return (arg);
}

int	append_arg(char **args, int *k, t_minishell *ms, int *i)
{
	char	*arg;

	if (ms->line[*i] == '<' || ms->line[*i] == '>' || ms->line[*i] == '|')
		arg = get_operator(ms, i);
	else
		arg = collect_argument(ms, i);
	if (!arg)
		return (0);
	if (arg != NULL && arg[0] != '\0')
	{
		args[*k] = arg;
		(*k)++;
	}
	return (1);
}

char	**parse_input(t_minishell *ms)
{
	char	**args;
	int		i;
	int		k;

	args = malloc(sizeof(char *) * 1024);
	if (!args)
		return (NULL);
	i = 0;
	k = 0;
	while (ms->line[i])
	{
		i = skip_spaces(ms->line, i);
		if (!ms->line[i])
			break ;
		if (!append_arg(args, &k, ms, &i))
		{
			free_all(args, k);
			return (NULL);
		}
	}
	args[k] = NULL;
	return (args);
}
