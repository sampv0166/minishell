/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:00 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 20:50:13 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*ft_strjoin2(char *saved_line, char *buffer)
{
	char	*new_string;
	int		total_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	total_len = ft_strlen(saved_line) + ft_strlen(buffer) + 1;
	new_string = (char *) malloc(sizeof(char) * (total_len));
	if (new_string == NULL)
		return (NULL);
	while (saved_line && saved_line[i])
		new_string[i++] = saved_line[j++];
	j = 0;
	while (buffer && buffer[j])
		new_string[i++] = buffer[j++];
	new_string[i] = '\0';
	return (new_string);
}

int	init(char ***path_splitted)
{
	char	*path;

	path = get_env_value("PATH");
	if (path == NULL)
		return (EXIT_FAILURE);
	*path_splitted = ft_split(path, ':');
	free(path);
	if (*path_splitted == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	free_path(char **dup, char **abs_path)
{
	free_me(dup);
	free_me(abs_path);
}

char	*get_abs_cmd(char *cmd)
{
	char	*abs_cmd_path;
	char	**path_split;
	char	*dup;
	int		i;

	i = 0;
	if (!cmd)
		return (cmd);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	init(&path_split);
	while (path_split[i])
	{
		abs_cmd_path = get_2d_path(abs_cmd_path, path_split, i, cmd);
		dup = ft_strdup(abs_cmd_path);
		if (abs_cmd_path == NULL)
			return (NULL);
		if (access(abs_cmd_path, X_OK) == 0)
			return (set_path(&path_split, &abs_cmd_path, &dup));
		else
			free_path(&dup, &abs_cmd_path);
		i++;
	}
	ft_free_split(path_split);
	return (NULL);
}
