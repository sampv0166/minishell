/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:29:47 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 20:34:54 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	close_pipe_and_heredoc_fd(t_pars_tokens *pa_tkns, int **p)
{
	if (g_env.open_heredoc_fdin != 0)
		close(g_env.open_heredoc_fdin);
	if (pa_tkns[0].pipe)
	{
		close_pipes_in_parent(p);
		free_pipes(p);
	}
	else
		free(p);
}

void	close_out_in_files_fd(t_pars_tokens *pa_tkns, int i)
{
	if (pa_tkns[i].is_in)
		close (g_env.open_fd_in);
	if (pa_tkns[i].is_out || pa_tkns[i].is_out_appnd)
	{
		close (g_env.open_fd_out);
	}
}

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
	(void)pid;
	while (i < g_env.count)
	{
		if (i == g_env.count - 1)
		{
			wait(&status);
			if (WIFEXITED(status))
				g_env.stat_code = WEXITSTATUS(status);
		}
		else
		{
			wait(&status);
			WIFEXITED(status);
		}
		i++;
	}
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
