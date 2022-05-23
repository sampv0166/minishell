/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arr_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:28:31 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:28:32 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	get_arr_len2(int *i, char *str, int *len, int trig)
{
	if (trig == 2)
	{
		(*i)++;
		if (str[*i] == 0)
			(*len)++;
	}
	else if (trig == 1)
	{
		(*i)++;
		(*len)++;
	}
}

static void	g_init(int *len, int *i)
{
	*len = 0;
	*i = 0;
}

int	get_arr_len(char *str)
{
	int	len;
	int	i;

	g_init(&len, &i);
	while (str[i])
	{
		if (str[i] == ' ')
			get_arr_len2(&i, str, &len, 1);
		else if (str[i] != ' ' && str[i])
		{
			if (str[i] == '\"')
			{
				if (!skip_and_increment_len_dbl_qts (str, &i, &len))
					break ;
			}
			else if (str[i] == '\'')
			{
				if (!skip_and_increment_len_sngl_qts (str, &i, &len))
					break ;
			}
			else
				get_arr_len2(&i, str, &len, 2);
		}
	}
	return (len);
}
