#include "minishell.h"

void	init_shell(t_minishell *sh)
{
	sh->line = NULL;
	sh->args = NULL;
	sh->prompt = NULL;
	sh->envp = NULL;
	sh->path_dirs = NULL;
	sh->pipe_fds = NULL;
	sh->pipe_count = 0;
	sh->in_fd = 0;
	sh->out_fd = 1;
	sh->last_exit_code = 0;
	sh->is_running = 1;
}
