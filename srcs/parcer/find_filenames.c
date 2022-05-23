/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_filenames.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:28:06 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:28:07 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	get_files_arr_len(t_pars_tokens *pa_tkns, int i)
{
	int	len ;
	int	j;

	len = 0;
	j = 0;
	get_cmd_len(pa_tkns, i, &j, &len);
	get_file_len(pa_tkns, i, &j, &len);
	return (len);
}

void	find_cmd_name(t_pars_tokens *pa_tkns, t_parser_info *pa_info, int i)
{
	while (pa_tkns[i].cmd_splitted[pa_info->j])
	{
		if (pa_tkns[i].cmd_splitted[pa_info->j]
			&& (pa_tkns[i].cmd_splitted[pa_info->j][0] == '<'
			|| pa_tkns[i].cmd_splitted[pa_info->j][0] == '>'))
		{
			pa_info->j++;
			if (pa_tkns[i].cmd_splitted[pa_info->j])
				pa_info->j++;
		}
		if (pa_tkns[i].cmd_splitted[pa_info->j]
			&& (pa_tkns[i].cmd_splitted[pa_info->j][0] == '<'
			|| pa_tkns[i].cmd_splitted[pa_info->j][0] == '>'))
			continue ;
		else if (pa_tkns[i].cmd_splitted[pa_info->j])
		{
			pa_info->arr[pa_info->len++]
				= ft_strdup(pa_tkns[i].cmd_splitted[pa_info->j]);
			pa_info->j++;
		}
		else
			break ;
	}
}

void	find_file_names(t_pars_tokens *pa_tkns,
		t_parser_info *pa_info, int i)
{
	while (pa_tkns[i].cmd_splitted[pa_info->j])
	{
		if (pa_tkns[i].cmd_splitted[pa_info->j]
			&& (pa_tkns[i].cmd_splitted[pa_info->j][0] == '<'
			|| pa_tkns[i].cmd_splitted[pa_info->j][0] == '>'))
		{
			pa_info->j++;
			if (pa_tkns[i].cmd_splitted[pa_info->j])
				pa_info->j++;
		}
		if (pa_tkns[i].cmd_splitted[pa_info->j]
			&& (pa_tkns[i].cmd_splitted[pa_info->j][0] == '<'
			|| pa_tkns[i].cmd_splitted[pa_info->j][0] == '>'))
			continue ;
		else if (pa_tkns[i].cmd_splitted[pa_info->j])
		{
			pa_info->arr[pa_info->len++]
				= ft_strdup(pa_tkns[i].cmd_splitted[pa_info->j]);
			pa_info->j++;
		}
		else
			break ;
	}
}

char	**find_input_file_names(t_pars_tokens *pa_tkns, int i)
{
	t_parser_info	pa_info;

	pa_info.j = 0;
	pa_info.len = 0;
	pa_info.k = get_files_arr_len(pa_tkns, i);
	pa_info.arr = (char **)malloc (sizeof(char *) * (pa_info.k + 1));
	find_cmd_name(pa_tkns, &pa_info, i);
	find_file_names(pa_tkns, &pa_info, i);
	pa_info.arr[pa_info.len] = NULL;
	pa_info.j = 0;
	return (pa_info.arr);
}
