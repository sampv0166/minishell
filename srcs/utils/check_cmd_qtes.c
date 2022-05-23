/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_qtes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:27:12 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:27:13 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	init_qtes(int *qte, int *i)
{
	*qte = 0;
	(*i)++;
}

int	parse_cmd(char *str)
{
	int	i;
	int	qte;

	i = 0;
	qte = 0;
	while (str[i])
	{
		if (ft_isqt(str[i]))
		{
			qte = str[i];
			i++;
			while (str[i] && str[i] != qte)
				i++;
			if (str[i] && str[i] == qte)
				init_qtes(&qte, &i);
			else
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	check_cmds_qtes(char **str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] != NULL)
	{
		ret = parse_cmd(str[i]);
		if (ret)
			break ;
		i++;
	}
	return (ret);
}
