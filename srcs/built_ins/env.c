/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:24 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:26 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"
/*Allocation done and put values here*/

static char	*getting_var(char *str, int len)
{
	char	*env_s;

	env_s = NULL;
	while (str[len] && ft_isenv(str[len]))
		len++;
	env_s = ft_calloc(sizeof(char), len + 1);
	len = 1;
	while (str[len] && ft_isenv(str[len]))
	{
		env_s[len - 1] = str[len];
		len++;
	}
	env_s[len - 1] = '\0';
	return (env_s);
}

static char	*getting_ret(int g_env1, int i, int j)
{
	char	*ret;

	ret = NULL;
	ret = ft_calloc(sizeof(char), j + 1);
	i = i - j;
	j = 0;
	while (g_env.env_var[g_env1][i])
	{
		ret[j] = g_env.env_var[g_env1][i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

/*Iterating towards = sign*/
/*Iterating towards \0 and counting all the characters with variable j*/
/*Allocation and putting values of the env variable*/

static char	*getting_value(int g_env1)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	ret = NULL;
	j = 0;
	while (g_env.env_var[g_env1][i] != '=' && g_env.env_var[g_env1][i] != '\0')
		i++;
	if (g_env.env_var[g_env1][i] == '=')
	{
		++i;
		j = 0;
		while (g_env.env_var[g_env1][i])
		{
			i++;
			j++;
		}
		ret = getting_ret(g_env1, i, j);
		return (ret);
	}
	return (NULL);
}

/*Returning the str value of the env varibale in fetching*/
/*Fetch for exit codes*/
/*This while loop to count how much memory we need for 
the environment variable which we're looking to fetch*/
/*Getting the index of the env variable*/
char	*get_env_dollar(char *str)
{
	int		j;
	char	*ret;

	j = 1;
	ret = malloc(sizeof(char));
	if (str[j] == '?')
	{
		free(ret);
		ret = ft_itoa(g_env.stat_code);
		return (ret);
	}
	else if (ft_isenv(str[j]))
	{
		free(ret);
		ret = getting_var(str, j);
		if (g_env.env_var[get_env(ret)] != NULL)
		{
			j = get_env(ret);
			free(ret);
			ret = getting_value(j);
			return (ret);
		}
	}
	free(ret);
	return (NULL);
}

int	env_var(void)
{
	ft_putstr_2d(g_env.env_var);
	return (0);
}
