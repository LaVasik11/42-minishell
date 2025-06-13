/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:35 by gkankia           #+#    #+#             */
/*   Updated: 2025/06/13 18:34:17 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_command(t_minishell *ms)
{
	char	*prompt;	

	prompt = get_prompt(ms);
	ms->line = readline(prompt);
	free(prompt);
	prompt = NULL;
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

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	(void)argc;
	(void)argv;
	init_shell(&ms);
	if (!init_env(&ms, envp))
	{
		perror("init_env");
		return (1);
	}
	setup_signals();
	while (ms.is_running)
		process_command(&ms);
	free_minishell(&ms);
	return (0);
}
