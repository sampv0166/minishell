/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:29:51 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:29:52 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	free_pipes(int **p)
{
	int	l;

	l = 0;
	while (l < g_env.count)
	{
		free(p[l]);
		l++;
	}
	free(p);
}

void	close_pipes_in_parent(int **p)
{	
	int	j;

	j = 0;
	while (j < g_env.count)
	{
		close(p[j][0]);
		close(p[j][1]);
		j++;
	}
}

void	re_init_fds_nd_path(char **path)
{
	*path = NULL;
	g_env.fd_in = 0;
	g_env.fd_out = 1;
}

int	get_2d_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	if (i != 0)
		i = i - 1;
	return (i);
}

int	get_2d_arr_len2(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
