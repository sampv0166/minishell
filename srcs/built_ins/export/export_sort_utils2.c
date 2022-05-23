/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:44 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:45 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

static char	**fetch_env_var(char **str)
{
	char	**var;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	var = (char **)malloc(sizeof(char *) * (length_2d(str) + 1));
	while (str[i] != NULL)
	{
		j = 0;
		len = ft_strlen(str[i]);
		var[i] = malloc(sizeof(char) * (len + 1));
		while (str[i][j] != '=')
		{
			var[i][j] = str[i][j];
			j++;
		}
		var[i][j] = '\0';
		i++;
	}
	var[i] = NULL;
	return (var);
}

static char	**fetch_env_values(char **str)
{
	int		i;
	int		j;
	int		k;
	char	**value;

	i = 0;
	value = (char **)malloc(sizeof(char *) * (length_2d(str) + 1));
	while (str[i] != NULL)
	{
		j = 0;
		k = 0;
		value[i] = malloc(sizeof(char) * (ft_strlen(str[i]) + 1));
		while (str[i][j] != '=')
			j++;
		while (str[i][j])
		{
			value[i][k] = str[i][j];
			j++;
			k++;
		}
		value[i][k] = '\0';
		i++;
	}
	value[i] = NULL;
	return (value);
}

static char	**vals_qtes(char **value, int len)
{
	char	**final;
	int		i;
	int		j;
	int		k;

	final = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (value[i] != NULL)
	{
		j = 0;
		k = 0;
		final[i] = ft_calloc(ft_strlen(value[i]) + 3, sizeof(char));
		if (value[i][j] == '=')
		{
			final[i][k++] = value[i][j++];
			final[i][k++] = 34;
			while (value[i][j])
				final[i][k++] = value[i][j++];
			final[i][k++] = 34;
			final[i][k] = '\0';
			i++;
		}
	}
	final[i] = NULL;
	return (final);
}

static char	**final_output(char **var, char **final, int len)
{
	int		i;
	int		trig;
	char	**res;

	i = 0;
	trig = 0;
	res = (char **)malloc(sizeof(char *) * (len + 2));
	trig = check_old_pwd(var);
	while (final[i] != NULL)
	{
		res[i] = ft_strdup("declare -x ");
		if (!trig && (var[i][0] == 'P'))
		{
			res[i] = ft_strjoin(res[i], "OLDPWD");
			trig = 1;
			i++;
			res[i] = ft_strdup("declare -x ");
		}
		res[i] = ft_strjoin(res[i], var[i]);
		res[i] = ft_strjoin(res[i], final[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**declare_s(char **str)
{
	char	**res;
	char	**value;
	char	**var;
	char	**final;

	var = fetch_env_var(str);
	value = fetch_env_values(str);
	final = vals_qtes(value, length_2d(str));
	res = final_output(var, final, length_2d(str));
	free_2d_array(final);
	free_2d_array(value);
	free_2d_array(var);
	return (res);
}
