#include "../../includes/mini_shell.h"

extern t_env_var	env;

void	restore_fds(void)
{
	if (env.open_heredoc_fdin != 0)
		close (env.open_heredoc_fdin);
	dup2(env.tmp_in, 0);
	dup2(env.tmp_out, 1);
	close(env.tmp_in);
	close(env.tmp_out);
}

void	wait_for_child_and_restore_fds_(pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < env.count)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	restore_fds();
}

void	init_and_dup_fd(void)
{
	env.tmp_in = dup(0);
	env.tmp_out = dup(1);
	env.fd_in = env.tmp_in ;
	env.fd_out = env.tmp_out;
	env.fd_pipe_in_open = 0;
	env.fd_pipe_out_open = 0;
}

void	init_redir_helper_fds(void)
{
	env.open_fd_in = 0;
	env.open_fd_out = 0;
	env.open_heredoc_fdin = 0;
}

void	close_fds(t_pars_tokens *pa_tkns, int i, int f)
{
	if (f == 0)
	{
		if (pa_tkns[i].pipe == 3)
			close(env.fd_pipe_in_open);
		if (pa_tkns[i].pipe == 1)
			close(env.fd_pipe_in_open);
		return ;
	}
	if (pa_tkns[i].is_in)
		close (env.open_fd_in);
	if (pa_tkns[i].is_out)
		close (env.open_fd_out);
	if (pa_tkns[i].pipe == 1)
	{
		close(env.fd_pipe_in_open);
		close(env.fd_pipe_out_open);
	}
	if (pa_tkns[i].pipe == 2)
		close(env.fd_pipe_out_open);
}
