#include "../../includes/mini_shell.h"

int	call_execve(t_pars_tokens *pa_tokens, char *abs_path, int i)
{
	if (!ft_strcmp(pa_tokens[i].cmd[0], "./minishell"))
		increment_s_vals();
	if (execve(abs_path, pa_tokens[i].cmd, g_env.env_var) == -1)
	{
		g_env.stat_code = 127;
		ft_putstr_fd(":-:command not found\n", 2);
	}
	return (g_env.stat_code);
}

void	wait_for_child(pid_t *pid)
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

void	create_pipes(t_pars_tokens *pa_tkns, char *path, pid_t *pid)
{
	int	i;
	int	**p;

	i = 0;
	p = malloc (sizeof (int **) * g_env.count);
	while (i < g_env.count && pa_tkns[i].pipe)
	{
		p[i] = malloc (sizeof (int) * 2);
		pipe(p[i]);
		i++;
	}	
	execute_commands(pa_tkns, path, pid, p);
}
