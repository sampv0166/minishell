/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:48:02 by apila-va          #+#    #+#             */
/*   Updated: 2022/05/22 18:24:57 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_atoi(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument requred", 2);
}

static int	check_limit(int i, int sign, char *str)
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

static long int	ft_atoi_atoi(char *str, int sign, int *index)
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
		if (check_limit(i, sign, str))
			return (nbr);
	}
	print_atoi(str);
	return (255);
}

long int	ft_atoi(const char *str)
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
	nbr = ft_atoi_atoi(s, sign, &i);
	return (nbr);
}
