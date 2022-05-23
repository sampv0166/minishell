/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:27:31 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:27:32 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	ft_isenv(char c)
{
	if (c == '_')
		return (1);
	else if (ft_isalpha(c))
		return (1);
	else if (ft_isdigit(c))
	{
		if (c == '+' || c == '-')
			return (0);
		return (1);
	}
	else if (c == '\\')
		return (1);
	return (0);
}
