/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:29:19 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 14:29:20 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

static void	print_atoi_exit(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument requred", 2);
}

static int	check_limit_exit(int i, int sign, char *str)
{
	if (i == 19 && sign > 0)
	{
		if (ft_strncmp(str, "9223372036854775808", 19) < 0)
			return (1);
	}
	else if (sign < 0 && (i == 20))
	{
		if (ft_strncmp(str, "-9223372036854775809", 20) < 0)
			return (1);
	}
	return (0);
}

static long int	ft_exit_atoi_atoi(char *str, int sign, int *index)
{
	int			i;
	long int	nbr;

	i = 0;
	i = *index;
	nbr = 0;
	if ((str[i] >= '0') && (str[i] <= '9'))
	{
		while ((str[i] >= '0') && (str[i] <= '9'))
		{
			nbr = (nbr * 10) + (str[i] - '0');
			i++;
		}
		nbr = nbr * sign;
		if (str[i] == '\0' || str[i] == ' ')
		{
			if (i < 19)
				return (nbr);
		}
		if (check_limit_exit(i, sign, str))
			return (nbr);
	}
	print_atoi_exit(str);
	g_env.n_trig = 1;
	return (255);
}

long int	ft_exit_atoi(const char *str)
{
	int		i;
	long	nbr;
	char	*s;
	int		sign;

	i = 0;
	s = (char *)str;
	sign = 1;
	while (s[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nbr = ft_exit_atoi_atoi(s, sign, &i);
	return (nbr);
}
