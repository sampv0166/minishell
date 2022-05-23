/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_2d_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:29:57 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:29:58 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static char	*get_abs_cmd_path(char **abs_cmd_path,
		char *path_splitted, char *cmd)
{
	*abs_cmd_path = ft_strjoin2(path_splitted, "/");
	if (abs_cmd_path == NULL)
		return (NULL);
	*abs_cmd_path = ft_strjoin(*abs_cmd_path, cmd);
	if (*abs_cmd_path == NULL)
		return (*abs_cmd_path);
	return (*abs_cmd_path);
}

char	*get_2d_path(char *abs, char **path_split, int i, char *cmd)
{
	char	**tmp;

	tmp = ft_split(cmd, ' ');
	abs = get_abs_cmd_path(&abs, path_split[i], tmp[0]);
	free_2d_array(tmp);
	return (abs);
}
