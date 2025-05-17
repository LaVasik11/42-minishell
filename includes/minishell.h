/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkankia <gkankia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:56:22 by gkankia           #+#    #+#             */
/*   Updated: 2025/05/16 18:40:15 by gkankia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/wait.h>
# include <limits.h>
# include <linux/limits.h>
# include "libft.h"
# include <signal.h>

# define MAX_ARGS 100

typedef struct s_minishell
{
	char	*line;
	char	**args;
	char	*prompt;
	char	**envp;
	char	**path_dirs;
	int		last_exit_code;
	int		pipe_count;
	int		*pipe_fds;
	int		in_fd;
	int		out_fd;
	int		is_running;
	int		exit_code;
}	t_minishell;


void	init_shell(t_minishell *sh);
void	setup_signals(void);
void	execute_command(t_minishell *sh);
void	free_minishell(t_minishell *sh);

char	**parse_input(t_minishell *ms);
int		append_arg(char **args, int *k, t_minishell *ms, int *i);
char	*copy_quoted_arg(t_minishell *ms, int *i);
char	*copy_unquoted_arg(t_minishell *ms, int *i);
char	*copy_double_quoted(t_minishell *ms, int *i, int end);
char	*copy_double_quoted_part(t_minishell *ms, int *i, int end, char *result);
char	*parse_dollar(t_minishell *ms, int *i);
char	*copy_single_quoted(char *line, int *i, int end);
char	*copy_segment(char *line, int start, int end);
char	*copy_unquoted_segment(char *line, int *i);
int		skip_spaces(char *line, int i);
int		find_closing_quote(char *line, int i, char quote);
int		is_quote(char c);
int		is_special(char c);
void	free_all(char **args, int count);
char	*str_join_free(char *s1, char *s2);
char	*get_env_value(char *name);

void	free_all(char **args, int count);
void	free_args(char **args);
char	*get_prompt(void);
char	*find_in_path(char *cmd);
char	*join_path(char *dir, char *cmd);
void	exit_with_error(t_minishell *sh, const char *msg);

#endif
