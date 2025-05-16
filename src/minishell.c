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

void	process_command(t_minishell *sh)
{
	sh->prompt = get_prompt();
	sh->line = readline(sh->prompt);
	free(sh->prompt);
	sh->prompt = NULL;
	if (sh->line == NULL)
	{
		printf("\nexit\n");
		sh->is_running = 0;
		return ;
	}
	add_history(sh->line);
	sh->args = parse_input(sh->line);
	if (sh->args && sh->args[0] != NULL)
		execute_command(sh);
	free_args(sh->args);
	sh->args = NULL;
	free(sh->line);
	sh->line = NULL;
}

int	main(void)
{
	t_minishell	sh;

	init_shell(&sh);
	setup_signals();
	while (sh.is_running)
		process_command(&sh);
	free_minishell(&sh);
	return (0);
}
