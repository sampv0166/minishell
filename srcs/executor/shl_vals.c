/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shl_vals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:09 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:10 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*set_path(char ***path_split, char **abs_path, char **dup)
{
	ft_free_split(*path_split);
	g_env.split = *path_split;
	free_me(abs_path);
	return (*dup);
}

void	placing_vals_shlvl(char *str)
{
	int		i;
	char	*tmp;

	i = get_env("SHLVL");
	tmp = NULL;
	if (g_env.env_var[i] == NULL)
	{
		tmp = ft_strdup("SHLVL=");
		tmp = ft_strjoin(tmp, str);
		g_env.env_var = new_env(tmp);
		free(tmp);
	}
	else
	{
		free(g_env.env_var[i]);
		g_env.env_var[i] = ft_strdup("SHLVL=");
		g_env.env_var[i] = ft_strjoin(g_env.env_var[i], str);
	}
	free(str);
}

void	increment_s_vals(void)
{
	int		i;
	char	*tmp;
	char	*str;

	str = NULL;
	g_env.s_pid = 0;
	tmp = ft_strdup("$");
	tmp = ft_strjoin(tmp, "SHLVL");
	i = get_env("SHLVL");
	if (g_env.env_var[i] == NULL)
		str = ft_strdup("0");
	else
		str = get_env_dollar(tmp);
	free(tmp);
	i = ft_atoi(str);
	i++;
	free(str);
	str = ft_itoa(i);
	placing_vals_shlvl(str);
}
