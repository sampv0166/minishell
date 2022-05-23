/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:28 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:29 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	pwd(char **str)
{
	int		i;
	char	*s;
	char	dir[1000];

	i = 0;
	while (str[i] != NULL)
	{
		if (is_rdr(str[i]))
			break ;
		else if (!ft_strcmp(str[i], "|"))
			break ;
		i++;
	}
	s = get_env_dollar("$PWD");
	if (s == NULL)
		s = ft_strdup(getcwd(dir, 1000));
	ft_putendl_fd(s, g_env.fd_out);
	free(s);
	return (0);
}
