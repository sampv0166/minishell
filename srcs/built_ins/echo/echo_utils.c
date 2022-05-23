/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:31:07 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:31:08 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

void	check_qtes(char *tmp, int j, int *i, t_flags *flags)
{
	if (tmp[j] == 34 || tmp[j] == 39)
	{
		flags->newl_flag = 1;
		(*i)++;
	}
	free(tmp);
	flags->trigger = 1;
}

int	operations(char *tmp, t_flags *flags, int *i)
{
	int	j;

	j = 0;
	while (tmp[j])
	{
		if (tmp[j] == '-' && !j && tmp[j + 1] == 'n')
		{
			j++;
			while (tmp[j] == 'n')
				j++;
			if (tmp[j] != '\0')
			{
				check_qtes(tmp, j, i, flags);
				return (*i);
			}
			flags->newl_flag = 1;
		}
		else
		{
			free(tmp);
			flags->trigger = 1;
			return (*i);
		}
	}
	return (0);
}

int	is_rdr_flag(char *str)
{
	if (!ft_strcmp(str, "<") && g_env.pa_tkns->is_in)
		return (1);
	else if (!ft_strcmp(str, ">") && g_env.pa_tkns->is_out)
		return (1);
	else if (!ft_strcmp(str, ">>") && g_env.pa_tkns->is_out_appnd)
		return (1);
	else if (!ft_strcmp(str, "<<") && g_env.pa_tkns->here_doc)
		return (1);
	return (0);
}

void	ft_init(t_flags *flags)
{
	flags->i = 0;
	flags->print_flag = 0;
	flags->newl_flag = 0;
	flags->qte = 0;
	flags->trigger = 0;
	flags->end = 0;
	flags->rdr_pip_index = 0;
}

/*Checking for double or single quotes, First reason
 is to not print them, Second if there is a double
quote or No quote and there is a $ in a str it should 
fetch the value of the env variable*/
int	check_rdr_pipes(char *str, t_flags *flags)
{
	if (str[0] == 39 || str[0] == 34)
		flags->qte = str[0];
	else if (last_char(str) == 39
		|| last_char(str) == 34)
		flags->qte = last_char(str);
	if (ft_strchr(str, '>') || ft_strchr(str, '<')
		|| ft_strchr(str, '|'))
	{
		if (is_rdr_flag(str))
		{
			flags->print_flag = 1;
			return (1);
		}
		else if (ft_strchr(str, '|'))
		{
			if (!ft_strcmp(str, "|") && g_env.pa_tkns->pipe)
			{
				flags->print_flag = 1;
				return (1);
			}
		}
	}
	return (0);
}
