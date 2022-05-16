#include "../../includes/mini_shell.h"

int	call_execve(t_pars_tokens *pa_tokens, char *abs_path, int i)
{
	if (!ft_strcmp(pa_tokens[i].cmd[0], "./minishell"))
		increment_s_vals();
	if (execve(abs_path, pa_tokens[i].cmd, g_env.env_var) == -1)
	{
		g_env.stat_code = 127;
		ft_putstr_fd(":-:command not found\n", 2);
		exit(127);
	}
	return (g_env.stat_code);
}

static void	end_process(t_pars_tokens *pa_tkns, pid_t *pid)
{
	close(g_env.tmp_in);
	close(g_env.tmp_out);
	if (g_env.fd_pipe_in_open != 0)
		close(g_env.fd_pipe_in_open);
	free_everything(pa_tkns);
	free(pid);
}

void	exec_child(t_pars_tokens *pa_tkns, pid_t *pid, char *path, int i)
{
	int	k;

	k = i;
	if (!is_inbuilt(pa_tkns[k].cmd[0]) && path)
	{
		close(g_env.tmp_in);
		close(g_env.tmp_out);
		if (pa_tkns[k].pipe != 0)
			close(g_env.fd_pipe_in_open);
		call_execve(pa_tkns, path, k);
		if (k == g_env.count - 1)
		{
			free_everything(pa_tkns);
			free_env();
			free(pid);
		}
	}
	else
		end_process(pa_tkns, pid);
}

void	execute_commands(t_pars_tokens *pa_tkns, char *path, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < g_env.count)
	{
		path = NULL;
		if (handle_in_redirections(pa_tkns, &i))
			continue ;
		dup2(g_env.fd_in, 0);
		close(g_env.fd_in);
		close_fds(pa_tkns, i, 0);
		g_env.stat_code = execute_cmd(pa_tkns, i, &path);
		close_fds(pa_tkns, i, 1);
		pid[i] = fork();
		g_env.s_pid = pid[i];
		if (pid[i] < 0)
			exit(0);
		if (pid[i] == 0)
		{
			exec_child(pa_tkns, pid, path, i);
			exit (0);
		}
		free_me(&path);
		i++;
	}
}

int	executor(t_pars_tokens *pa_tkns)
{
	pid_t	*pid;
	char	*path;

	path = NULL;
	pid = ft_calloc(sizeof(pid_t), g_env.count);
	init_and_dup_fd();
	execute_commands(pa_tkns, path, pid);
	wait_for_child_and_restore_fds_(pid);
	free(pid);
	return (0);
}
