/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:31 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:32 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	elimination(char *str)
{
	char	*s;
	int		i;
	int		index;

	i = 0;
	index = 0;
	s = ft_strdup(g_env.env_var[0]);
	i = get_env(str);
	index = i;
	if (g_env.env_var[index] != NULL)
	{
		i = index;
		while (g_env.env_var[i + 1] != NULL)
		{
			free(g_env.env_var[i]);
			g_env.env_var[i] = ft_strdup(g_env.env_var[i + 1]);
			i++;
		}
		free(g_env.env_var[i]);
		g_env.env_var[i] = NULL;
	}
	free(s);
}

static char	*get_unset_env(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	delimit_qtes(str);
	if (ft_isdigit(str[i]))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
			return (NULL);
		i++;
	}
	tmp = ft_strdup(str);
	return (tmp);
}

static int	parse_unset(char *str)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	j = 0;
	if (!is_rdr(str) || ft_strcmp(str, "|"))
	{
		tmp = get_unset_env(str);
		if (tmp == NULL)
		{
			ft_putstr_fd("Not a valid identifier\n", 2);
			return (1);
		}
		j = 0;
		while (tmp[j])
		{
			str[j] = tmp[j];
			j++;
		}
		str[j] = '\0';
		free(tmp);
	}
	return (0);
}

int	unset(char **str)
{
	int	i;

	i = 1;
	while (str[i] != NULL)
	{
		g_env.stat_code = parse_unset(str[i]);
		if (is_rdr(str[i]) || !ft_strcmp(str[i], "|"))
			break ;
		if (!g_env.stat_code)
			elimination(str[i]);
		i++;
	}
	return (g_env.stat_code);
}
