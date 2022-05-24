/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:28:18 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 19:15:10 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	init_pa_tkns(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
	int	i;

	i = 2;
	while (i < pa_info->pipes_count)
	{
		pa_tkns[i].cmd = NULL;
		pa_tkns[i].cmd_full = NULL;
		pa_tkns[i].cmd_splitted = NULL;
		pa_tkns[i].cmd_cpy = NULL;
		pa_tkns[i].pipe_read_end = 0;
		pa_tkns[i].pipe_write_end = 0;
		pa_tkns[i].pipe = 0;
		pa_tkns[i].is_in = 0;
		pa_tkns[i].is_out = 0;
		pa_tkns[i].is_out_appnd = 0;
		pa_tkns[i].fd_in = 0;
		pa_tkns[i].fd_out = 0;
		pa_tkns[i].here_doc = 0;
		pa_tkns[i].fd_out = 0;
		pa_tkns[i].here_doc = 0;
		i++;
	}
}

void	init_pa_tkns_info(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
	pa_tkns[pa_info->j].fd_in = 0;
	pa_tkns[pa_info->j].fd_out = 0;
	pa_tkns[pa_info->j].is_in = 0;
	pa_tkns[pa_info->j].is_out = 0;
	pa_tkns[pa_info->j].is_out_appnd = 0;
	pa_tkns[pa_info->j].pipe = 0;
	pa_tkns[pa_info->j].here_doc = 0;
}

static void	trigger_pa_tkns(t_pars_tokens *pa_tkns,
	t_parser_info *pa_info, int trig)
{
	if (trig == 1)
	{
		pa_tkns[pa_info->j].pipe_read_end = 1;
		pa_tkns[pa_info->j].pipe_write_end = 1;
		pa_tkns[pa_info->j].pipe = 3;
	}
	else if (trig == 2)
	{
		pa_tkns[pa_info->j].pipe_read_end = 0;
		pa_tkns[pa_info->j].pipe_write_end = 1;
		pa_tkns[pa_info->j].pipe = 2;
	}
	else if (trig == 3)
	{
		pa_tkns[pa_info->j].pipe_read_end = 1;
		pa_tkns[pa_info->j].pipe_write_end = 0;
		pa_tkns[pa_info->j].pipe = 1;
	}
}

void	set_pipe_type(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
	pa_info->j = 0;
	while (pa_info->j < g_env.count)
	{
		if ((pa_tkns[pa_info->j].cmd_full && pa_tkns[pa_info->j].cmd_full[0]
				== '|') && (pa_tkns[pa_info->j].cmd_full[
					ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] == '|'))
		{
			trigger_pa_tkns(pa_tkns, pa_info, 1);
		}
		else if (pa_tkns[pa_info->j].cmd_full && pa_tkns[pa_info->j].cmd_full[0]
			!= '|' && pa_tkns[pa_info->j].cmd_full[
				ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] == '|')
		{
			trigger_pa_tkns(pa_tkns, pa_info, 2);
		}
		else if (pa_tkns[pa_info->j].cmd_full && pa_tkns[pa_info->j].cmd_full[0]
			== '|' && pa_tkns[pa_info->j].cmd_full[
				ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] != '|')
		{
			trigger_pa_tkns(pa_tkns, pa_info, 3);
		}
		pa_info->j++;
	}
}

void	set_redirection_type(t_pars_tokens *pa_tkns,
		t_parser_info *pa_info, char **tokens)
{
	if (tokens[pa_info->i][0] == '>' && tokens[pa_info->i][1] == '>')
		pa_tkns[pa_info->j].is_out_appnd = 1;
	else if (tokens[pa_info->i][0] == '>')
		pa_tkns[pa_info->j].is_out = 1;
	if (tokens[pa_info->i][0] == '<' && tokens[pa_info->i][1] == '<')
	{
		read_here_doc(tokens, pa_info, pa_tkns);
		pa_tkns[pa_info->j].here_doc = 1;
	}
	else if (tokens[pa_info->i][0] == '<')
		pa_tkns[pa_info->j].is_in = 1;
}
