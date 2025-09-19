/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: georgy-kankiya <georgy-kankiya@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:55:35 by gkankia           #+#    #+#             */
/*   Updated: 2025/09/19 15:07:19 by georgy-kank      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_command(t_minishell *sh)
{
	char	*prompt;	

	prompt = get_prompt(sh);
	sh->line = readline(prompt);
	check_signal(sh);
	free(prompt);
	prompt = NULL;
	if (sh->line == NULL)
	{
		printf("\nexit\n");
		sh->is_running = 0;
		return ;
	}
	add_history(sh->line);
	sh->args = parse_input(sh);
	if (sh->args && sh->args[0] != NULL)
		execute_command(sh);
	free_args(sh->args);
	sh->args = NULL;
	free(sh->line);
	sh->line = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sh;

	(void)argc;
	(void)argv;
	init_shell(&sh);
	if (!init_env(&sh, envp))
	{
		free_array(sh.envp);
		perror("init_env");
		return (1);
	}
	setup_signals();
	while (sh.is_running)
		process_command(&sh);
	free_minishell(&sh);
	return (sh.exit_code);
}
