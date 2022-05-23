/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:27:37 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:27:38 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_putstr_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_putendl_fd(str[i], g_env.fd_out);
		i++;
	}
}
