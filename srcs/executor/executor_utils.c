#include "../../includes/mini_shell.h"

void	restore_fds(void)
{
	if (g_env.open_heredoc_fdin != 0)
		close (g_env.open_heredoc_fdin);
	dup2(g_env.tmp_in, 0);
	dup2(g_env.tmp_out, 1);
	close(g_env.tmp_in);
	close(g_env.tmp_out);
}

void	wait_for_child_and_restore_fds_(pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	status = 2;
	while (i < g_env.count)
	{
		if (pid[i])
		{
			wait(&status);
			if (WIFEXITED(status))
				g_env.stat_code = WEXITSTATUS(status);
		}
		i++;
	}
	restore_fds();
}

void	init_and_dup_fd(void)
{
	g_env.tmp_in = dup(0);
	g_env.tmp_out = dup(1);
	g_env.fd_in = g_env.tmp_in ;
	g_env.fd_out = g_env.tmp_out;
	g_env.fd_pipe_in_open = 0;
	g_env.fd_pipe_out_open = 0;
}

void	init_redir_helper_fds(void)
{
	g_env.open_fd_in = 0;
	g_env.open_fd_out = 0;
	g_env.open_heredoc_fdin = 0;
}

void	close_fds(t_pars_tokens *pa_tkns, int i, int f)
{
	if (f == 0)
	{
		if (pa_tkns[i].pipe == 3)
			close(g_env.fd_pipe_in_open);
		if (pa_tkns[i].pipe == 1)
			close(g_env.fd_pipe_in_open);
		return ;
	}
	if (pa_tkns[i].is_in)
		close (g_env.open_fd_in);
	if (pa_tkns[i].is_out)
		close (g_env.open_fd_out);
	if (pa_tkns[i].pipe == 1)
	{
		close(g_env.fd_pipe_in_open);
		close(g_env.fd_pipe_out_open);
	}
	if (pa_tkns[i].pipe == 2)
		close(g_env.fd_pipe_out_open);
}
