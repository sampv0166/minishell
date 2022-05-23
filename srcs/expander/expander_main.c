/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:29:21 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:29:22 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	exp_init(int *j, int *m)
{
	*j = 0;
	*m = 0;
}

static char	**get_2d_exp2(int y, t_pars_tokens *pa_tkns, int m)
{
	char	*tmp;
	char	*res;
	int		j;
	char	**full;

	full = (char **)malloc(sizeof(char *) * (get_len(pa_tkns[y].cmd_splitted)
				+ 1));
	exp_init(&j, &m);
	res = NULL;
	tmp = NULL;
	while (pa_tkns[y].cmd_splitted[j] != NULL)
	{
		tmp = ft_strdup(pa_tkns[y].cmd_splitted[j]);
		res = parse_str(tmp);
		free(tmp);
		if (*res)
		{
			full[m] = ft_strdup(res);
			m++;
		}
		free(res);
		j++;
	}
	full[m] = NULL;
	return (full);
}

static char	**get_2d_exp(int y, t_pars_tokens *pa_tkns, int m)
{
	char	*tmp;
	char	*res;
	int		j;
	char	**full;

	full = (char **)malloc(sizeof(char *) * (get_len(pa_tkns[y].cmd) + 1));
	m = 0;
	j = 0;
	res = NULL;
	tmp = NULL;
	while (pa_tkns[y].cmd[j] != NULL)
	{
		tmp = ft_strdup(pa_tkns[y].cmd[j]);
		res = parse_str(tmp);
		free(tmp);
		if (*res)
		{
			full[m] = ft_strdup(res);
			m++;
		}
		free(res);
		j++;
	}
	full[m] = NULL;
	return (full);
}

void	expander(t_pars_tokens *pa_tkns)
{
	int		y;
	char	**full;
	char	**full_splitted;

	y = 0;
	while (y < g_env.count)
	{
		pa_tkns[y].cmd_cpy = ft_2d_str_cpy(pa_tkns[y].cmd);
		full_splitted = get_2d_exp2(y, pa_tkns, 0);
		ft_free_str_array(&pa_tkns[y].cmd_splitted);
		pa_tkns[y].cmd_splitted = ft_2d_str_cpy(full_splitted);
		free_2d_array(full_splitted);
		full = get_2d_exp(y, pa_tkns, 0);
		free_2d_array(pa_tkns[y].cmd);
		pa_tkns[y].cmd = ft_2d_str_cpy(full);
		free_2d_array(full);
		y++;
	}
}
