/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:35 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/16 17:55:36 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*user;
	char	*tmp;
	char	*prompt;

	user = getenv("USER");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup("minishell> "));
	if (!user)
		user = "user";
	tmp = ft_strjoin(user, ":");
	if (!tmp)
		return (ft_strdup("minishell> "));
	prompt = ft_strjoin(tmp, cwd);
	free(tmp);
	if (!prompt)
		return (ft_strdup("minishell> "));
	tmp = ft_strjoin(prompt, "$ ");
	free(prompt);
	if (!tmp)
		return (ft_strdup("minishell> "));
	return (tmp);
}

void	process_command(t_minishell *ms)
{
	ms->prompt = get_prompt();
	ms->line = readline(ms->prompt);
	free(ms->prompt);
	ms->prompt = NULL;
	if (ms->line == NULL)
	{
		printf("\nexit\n");
		ms->is_running = 0;
		return ;
	}
	add_history(ms->line);
	ms->args = parse_input(ms);
	if (ms->args && ms->args[0] != NULL)
		execute_command(ms);
	free_args(ms->args);
	ms->args = NULL;
	free(ms->line);
	ms->line = NULL;
}

int	main(void)
{
	t_minishell	ms;

	init_shell(&ms);
	setup_signals();
	while (ms.is_running)
		process_command(&ms);
	free_minishell(&ms);
	return (0);
}
