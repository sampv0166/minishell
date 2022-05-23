/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:26:57 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 16:34:20 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	free_env(void)
{
	ft_free_str_array(&g_env.env_var);
	return (0);
}

int	free_everything(t_pars_tokens *tokens)
{
	int	i;

	i = 0;
	while (g_env.count > 1 && i < g_env.count)
	{
		ft_free_str_array(&tokens[i].cmd);
		ft_free_str_array(&tokens[i].cmd_cpy);
		ft_free_str_array(&tokens[i].cmd_splitted);
		free_me(&tokens[i].cmd_full);
		i++;
	}
	if (g_env.count == 1)
	{
		free_2d_array(tokens[i].cmd);
		ft_free_str_array(&tokens[i].cmd_cpy);
		ft_free_str_array(&tokens[i].cmd_splitted);
		free_me(&tokens[i].cmd_full);
	}
	free(tokens);
	tokens = NULL;
	return (0);
}

void	print_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd(arr[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}

int	ft_perror(int exit_status, char *msg)
{
	perror(msg);
	g_env.stat_code = exit_status;
	return (exit_status);
}

void	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free_me(&split[i]);
		i++;
	}
	free(split);
	return (NULL);
}
