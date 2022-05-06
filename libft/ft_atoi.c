/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar <makhtar@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:48:02 by apila-va          #+#    #+#             */
/*   Updated: 2022/04/21 11:25:42 by makhtar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		if (i == 19 && sign > 0)
		{
			if (ft_strncmp(str, "9223372036854775808", 19) < 0)
				return (nbr);
		}
		else if (sign < 0 && (i == 20))
		{
			if (ft_strncmp(str, "-9223372036854775809", 20) < 0)
				return (nbr);
		}
	}
	// ft_putstr_fd("exit: ", 1);
	// ft_putstr_fd(str, 1);
	// ft_putendl_fd(": numeric argument requred", 1);
	// if (i >= 19)
	// 	return (255);
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
