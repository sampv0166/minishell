#include "../../includes/mini_shell.h"

void	close_pipes_in_child(int i, int **p)
{
	int	j;

	j = 0;
	while (j < g_env.count)
	{
		if (i != j)
			close(p[j][0]);
		if (i + 1 != j)
			close(p[j][1]);	
		j++;
	}
}

void	duplicate_fds(t_pars_tokens *pa_tkns, int i, int **p)
{
	if (pa_tkns[i].pipe && !pa_tkns[i].is_in && !pa_tkns[i].here_doc)
	{
		if (pa_tkns[i].pipe == 2)
			;
		else
			dup2(p[i][0], STDIN_FILENO);
	}
	else if (pa_tkns[i].is_in || pa_tkns[i].here_doc)
		dup2(g_env.fd_in, STDIN_FILENO);
	if (pa_tkns[i].pipe && !pa_tkns[i].is_out && !pa_tkns[i].is_out_appnd)
	{
		if (pa_tkns[i].pipe == 1)
			;
		else
			dup2(p[i + 1][1], STDOUT_FILENO);
	}
	else if (pa_tkns[i].is_out || pa_tkns[i].is_out_appnd)
		dup2(g_env.fd_out, STDOUT_FILENO);
}

void	exec_child(t_pars_tokens *pa_tkns, char *path, int i, int **p)
{
	int	k;

	k = i;
	close_pipes_in_child(i, p);
	if (!is_inbuilt(pa_tkns[k].cmd[0]) && path)
	{
		duplicate_fds(pa_tkns, i, p);
		call_execve(pa_tkns, path, k);
	}
	else if (is_inbuilt(pa_tkns[k].cmd[0]))
		;
	else
		g_env.stat_code = 127;
}

void	execute_commands(t_pars_tokens *pa_tkns, \
		char *path, pid_t *pid, int **p)
{
	int	i;

	i = 0;
	while (i < g_env.count)
	{
		re_init_fds_nd_path(&path);
		if (handle_in_redirections(pa_tkns, &i))
			continue ;
		g_env.stat_code = execute_cmd(pa_tkns, i, &path, p);
		pid[i] = fork();
		g_env.s_pid = pid[i];
		if (pid[i] < 0)
			exit(0);
		if (pid[i] == 0)
		{
			exec_child(pa_tkns, path, i, p);
			exit (g_env.stat_code);
		}
		if (pa_tkns[i].is_in)
			close (g_env.open_fd_in);
		if (pa_tkns[i].is_out)
			close (g_env.open_fd_out);		
		free_me(&path);
		i++;
	}
	close_pipes_in_parent(p);
	free_pipes(p);
}

int	executor(t_pars_tokens *pa_tkns)
{
	pid_t	*pid;
	char	*path;

	path = NULL;
	pid = ft_calloc(sizeof(pid_t), g_env.count);
	create_pipes(pa_tkns, path, pid);
	wait_for_child(pid);
	free(pid);
	return (0);
}
