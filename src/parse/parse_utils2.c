/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:13 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/16 17:55:14 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_segment(char *line, int start, int end)
{
	char	*segment;
	int		len;
	int		j;

	len = end - start;
	segment = malloc(len + 1);
	if (!segment)
		return (NULL);
	j = 0;
	while (start < end)
		segment[j++] = line[start++];
	segment[j] = '\0';
	return (segment);
}

char	*get_env_value(char *name)
{
	char	*value;

	if (!name || !*name)
		return (NULL);
	value = getenv(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*parse_dollar(t_minishell *ms, int *i)
{
	int		start;
	int		len;
	char	*name;
	char	*value;

	(*i)++;
	if (ms->line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(ms->exit_code));
	}
	start = *i;
	while (ms->line[*i] && (ft_isalnum(ms->line[*i]) || ms->line[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (ft_strdup("$"));
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, &ms->line[start], len + 1);
	value = get_env_value(name);
	free(name);
	return (value);
}

void	copy_or_empty(char *dst, char *src, size_t len)
{
	if (src)
		ft_strlcpy(dst, src, len);
	else
		dst[0] = '\0';
}

char	*str_join_free(char *s1, char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	copy_or_empty(joined, s1, len1 + 1);
	copy_or_empty(joined + len1, s2, len2 + 1);
	free(s1);
	free(s2);
	return (joined);
}
