/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:06 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 17:26:59 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	find_input_fd(t_pars_tokens *pa_tkns, int i)
{
	int	len;
	int	j;

	len = get_2d_arr_len(pa_tkns[i].cmd_splitted);
	j = len;
	while (j >= 0 && pa_tkns[i].cmd_splitted && pa_tkns[i].cmd_splitted[j])
	{
		if (pa_tkns[i].cmd_splitted[j] && pa_tkns[i].cmd_splitted[j][0] == '<')
		{
			if (ft_strlen(pa_tkns[i].cmd_splitted[j]) == 1)
				break ;
			else
			{
				g_env.fd_in = pa_tkns[i].here_doc_fd;
				g_env.open_heredoc_fdin = pa_tkns[i].here_doc_fd;
				break ;
			}
		}
		j--;
	}
}

int	check_for_input_files(t_pars_tokens *pa_tkns, int i)
{
	int	j;

	j = 0;
	find_cmd (pa_tkns, i, &j);
	while (pa_tkns[i].cmd_splitted && pa_tkns[i].cmd_splitted[j])
	{
		increment_j(pa_tkns, i, &j);
		if (pa_tkns[i].cmd_splitted[j] && (pa_tkns[i].cmd_splitted[j][0] == '<' \
			|| pa_tkns[i].cmd_splitted[j][0] == '>'))
			continue ;
		else if (pa_tkns[i].cmd_splitted[j])
		{
			j++;
			continue ;
		}
		else
			break ;
	}
	return (0);
}

int	open_fds(char **cmd_split, int i, int *fd_out, int *fd_in)
{
	if (cmd_split && cmd_split[i] && (cmd_split[i][0] == '>' \
		&& ft_strlen(cmd_split[i]) == 1 && cmd_split[i + 1]))
	{
		close_redir_fd(fd_out);
		*fd_out = open(cmd_split[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (*fd_out == -1)
			return (ft_perror(EXIT_FAILURE, "error opening file"));
	}
	if (cmd_split[i] && (cmd_split[i][0] == '>' && cmd_split[i][1] == '>' \
		&& ft_strlen(cmd_split[i]) == 2 && cmd_split[i + 1]))
	{
		close_redir_fd(fd_out);
		*fd_out = open(cmd_split[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (*fd_out == -1)
			return (ft_perror(EXIT_FAILURE, "error opening file"));
	}
	if (cmd_split[i][0] == '<' && ft_strlen(cmd_split[i]) == 1 \
		&& cmd_split[i + 1])
	{
		close_redir_fd(fd_in);
		*fd_in = open(cmd_split[i + 1], O_RDONLY);
		if (*fd_in == -1)
			return (ft_perror(EXIT_FAILURE, "error opening file"));
	}
	return (0);
}

int	open_files_fd(char **cmd_split, t_pars_tokens *pa_tokens, int tkn_idx)
{
	int	i;
	int	fd_out;
	int	fd_in;

	i = 0;
	fd_out = 0;
	fd_in = 0;
	while (cmd_split[i])
	{
		if (open_fds(cmd_split, i, &fd_out, &fd_in))
			return (EXIT_FAILURE);
		i++;
	}
	if (pa_tokens[tkn_idx].is_out || pa_tokens[tkn_idx].is_out_appnd)
	{
		g_env.open_fd_out = fd_out;
		g_env.fd_out = fd_out;
	}
	if (pa_tokens[tkn_idx].is_in)
	{
		g_env.open_fd_in = fd_in;
		g_env.fd_in = fd_in;
	}
	return (0);
}
//check_for_input_files(pa_tkns, i);

int	handle_in_and_here_doc(t_pars_tokens *pa_tkns, int i)
{
	if (open_files_fd(pa_tkns[i].cmd_splitted, pa_tkns, i) == EXIT_FAILURE)
		return (1);
	find_input_fd(pa_tkns, i);
	return (0);
}
