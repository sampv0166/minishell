/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:57 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 15:14:24 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

void	ft_exit_init(int *i, unsigned char *c)
{
	*i = 1;
	*c = g_env.stat_code;
	g_env.trigger = 0;
	g_env.n_trig = 0;
}

unsigned char	set_exit_triggers(unsigned char *c,
		int pipe, int *i, char **str)
{
	unsigned char	ret;

	ret = 0;
	g_env.stat_code = *c;
	if (g_env.trigger && pipe == 0)
		g_env.trigger = 1;
	else if (pipe != 0)
		g_env.trigger = 0;
	if ((*i) == 1 && str[*i] == NULL)
	{
		if (pipe)
		{
			*c = 0;
			g_env.trigger = 0;
		}
		else
			g_env.trigger = 1;
	}
	ret = *c;
	return (ret);
}
