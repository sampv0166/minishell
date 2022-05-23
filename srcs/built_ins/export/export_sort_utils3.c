/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:47 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:48 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

int	check_old_pwd(char **var)
{
	int	i;

	i = 0;
	while (var[i] != NULL)
	{
		if (!ft_strcmp(var[i], "OLDPWD"))
			return (1);
		i++;
	}
	return (0);
}
