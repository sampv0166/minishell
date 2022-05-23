/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:31:00 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 14:21:40 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

static void	ft_exit_print(char *str)
{
	g_env.trigger = 1;
	ft_putstr_fd("exit: ", 2);
	if (str == NULL)
		ft_putendl_fd("too many arguments", 2);
	else
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument requred", 2);
	}
}

static int	is_sign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

static int	check_args(char *str, int i, unsigned char *c)
{
	if (i > 1)
	{
		*c = 1;
		ft_exit_print(NULL);
		g_env.trigger = 0;
		return (1);
	}
	else if (i == 1)
		g_env.trigger = 1;
	*c = ft_exit_atoi(str);
	return (0);
}

static void	exit_is_alpha(char **str, int *i, unsigned char *c)
{
	ft_exit_print(str[*i]);
	*c = 255;
}

unsigned char	ft_exit(char **str, int pipe)
{
	unsigned char	c;
	int				i;

	ft_exit_init(&i, &c);
	while (str[i] != NULL)
	{
		if (is_rdr(str[i]) || !ft_strcmp(str[i], "|"))
			break ;
		delimit_qtes(str[i]);
		if (i > 1 || is_sign(str[i][0]) || ft_isdigit(str[i][0]))
		{
			if (check_args(str[i], i, &c) || g_env.n_trig)
				break ;
		}
		else if (ft_isalpha(str[i][0]) || ft_isqt(str[i][0]))
		{
			exit_is_alpha(str, &i, &c);
			break ;
		}
		i++;
	}
	return (set_exit_triggers(&c, pipe, &i, str));
}
