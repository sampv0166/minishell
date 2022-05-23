/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_str_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:27:24 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:27:25 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	**ft_2d_str_cpy(char **str)
{
	char	**cpy;
	int		i;
	int		len;

	len = get_2d_arr_len2(str);
	cpy = (char **)ft_calloc(sizeof(char *), (len + 1));
	i = 0;
	while (str[i] != NULL)
	{
		cpy[i] = ft_strdup(str[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
