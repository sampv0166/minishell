/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_filename_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:28:03 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:28:04 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	increment_k_l(int *k, int *l)
{
	(*k)++;
	(*l)++;
}

void	get_cmd_len(t_pars_tokens *pa_tkns, int i, int *j, int *len)
{
	int	k;
	int	l;

	l = *len;
	k = *j;
	while (pa_tkns[i].cmd_splitted[k])
	{
		if (pa_tkns[i].cmd_splitted[k] && (pa_tkns[i].cmd_splitted[k][0] == '<'
			|| pa_tkns[i].cmd_splitted[k][0] == '>'))
		{
			k++;
			if (pa_tkns[i].cmd_splitted[k])
				k++;
		}
		if (pa_tkns[i].cmd_splitted[k] && (pa_tkns[i].cmd_splitted[k][0] == '<'
			|| pa_tkns[i].cmd_splitted[k][0] == '>'))
			continue ;
		else if (pa_tkns[i].cmd_splitted[k])
			increment_k_l(&k, &l);
		else
			break ;
	}
	*j = k;
	*len = l;
}

void	get_file_len(t_pars_tokens *pa_tkns, int i, int *j, int *len)
{
	int	k;
	int	l;

	l = *len;
	k = *j;
	while (pa_tkns[i].cmd_splitted[k])
	{
		if (pa_tkns[i].cmd_splitted[k] && (pa_tkns[i].cmd_splitted[k][0] == '<'
			|| pa_tkns[i].cmd_splitted[k][0] == '>'))
		{
			k++;
			if (pa_tkns[i].cmd_splitted[k])
				k++;
		}
		if (pa_tkns[i].cmd_splitted[k] && (pa_tkns[i].cmd_splitted[k][0] == '<'
			|| pa_tkns[i].cmd_splitted[k][0] == '>'))
			continue ;
		else if (pa_tkns[i].cmd_splitted[k])
			increment_k_l(&k, &l);
		else
			break ;
	}
	*j = k;
	*len = l;
}
