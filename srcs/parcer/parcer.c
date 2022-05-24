/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:28:21 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 19:16:48 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	deal_with_pipes(t_pars_tokens *pa_tkns,
		t_parser_info *pa_info, char **tokens)
{
	pa_info->arr[pa_info->len] = ((char *)0);
	pa_info->str = ft_strjoin (pa_info->str, tokens[pa_info->i]);
	pa_info->arr1[pa_info->len] = ((char *)0);
	pa_info->len++;
	pa_info->i++;
	(void)pa_tkns;
}

void	create_cmds(t_parser_info *pa_info, char **tokens)
{
	pa_info->arr[pa_info->len] = ft_strdup(tokens[pa_info->i]);
	pa_info->arr1[pa_info->len] = ft_strdup(tokens[pa_info->i]);
	pa_info->str = ft_strjoin (pa_info->str, tokens[pa_info->i]);
	pa_info->len++;
	pa_info->i++;
}

void	parcer2(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
	char	**f;

	set_pipe_type(pa_tkns, pa_info);
	pa_info->i = 0;
	while (pa_info->i < g_env.count)
	{	
		f = find_input_file_names(pa_tkns, pa_info->i);
		ft_free_str_array(&pa_tkns[pa_info->i].cmd);
		pa_tkns[pa_info->i].cmd = f;
		pa_info->i++;
	}
}

void	parse_commands(char **tokens,
		t_parser_info *pa_info, t_pars_tokens *pa_tkns)
{
	while (tokens[pa_info->i])
	{
		if (pa_info->i > 0 && tokens[pa_info->i - 1]
			&& tokens[pa_info->i - 1][0] == '|')
			pa_info->str = ft_strjoin(pa_info->str, tokens[pa_info->i - 1]);
		if (tokens[pa_info->i][0] == '|')
		{
			deal_with_pipes(pa_tkns, pa_info, tokens);
			break ;
		}
		set_redirection_type(pa_tkns, pa_info, tokens);
		create_cmds(pa_info, tokens);
	}
}

t_pars_tokens	*parser(char **tokens)
{
	t_pars_tokens	*pa_tkns;
	t_parser_info	pa_info;

	init_parser_info(&pa_info, tokens);
	pa_tkns = malloc (sizeof (t_pars_tokens) * (pa_info.pipes_count));
	init_pa_tkns(pa_tkns, &pa_info);
	while (pa_info.j < pa_info.pipes_count)
	{
		init_pa_tkns_info(pa_tkns, &pa_info);
		allocate_cmd_memmory(&pa_info, tokens);
		parse_commands(tokens, &pa_info, pa_tkns);
		set_pa_tokens(pa_tkns, &pa_info);
		pa_info.j++;
	}
	parcer2(pa_tkns, &pa_info);
	return (pa_tkns);
}
