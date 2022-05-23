/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:38 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:39 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

static void	export_split_env(char *str)
{
	int		i;
	char	*var;
	char	*tmp;
	int		len;

	tmp = NULL;
	var = ft_strdup(str);
	i = 0;
	while (var[i] != '+')
		i++;
	var[i] = '\0';
	tmp = ft_calloc(1, ft_strlen(str) + 1);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	len = 0;
	while (str[i])
	{
		tmp[len] = str[i];
		len++;
		i++;
	}
	tmp[len] = '\0';
	export_new_env(var, tmp);
}

static void	export_append(char *str, char *var, int g_env1)
{
	char	*tmp;
	int		i;
	int		len;

	tmp = ft_calloc(1, ft_strlen(str) + 1);
	len = 0;
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	++i;
	while (str[i])
	{
		tmp[len] = str[i];
		len++;
		i++;
	}
	tmp[len] = '\0';
	var = ft_strdup(g_env.env_var[g_env1]);
	var = ft_strjoin(var, tmp);
	free(g_env.env_var[g_env1]);
	g_env.env_var[g_env1] = ft_strdup(var);
	free(var);
	free(tmp);
}

static int	plus_export(char *str)
{
	char	*var;
	int		g_env1;
	int		i;

	i = 0;
	g_env1 = 0;
	var = ft_strdup(str);
	while (var[i] != '+')
		i++;
	var[i] = '\0';
	g_env1 = get_env(var);
	free(var);
	var = NULL;
	if (g_env.env_var[g_env1] == NULL)
		export_split_env(str);
	else
		export_append(str, var, g_env1);
	return (0);
}

static int	append_expo(char *var)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (var[i] != '+')
		i++;
	if (var[i + 1] == '=' && !op_not(var[i - 1]))
	{
		ret = plus_export(var);
		free(var);
		return (ret);
	}
	else
	{
		error_print(NULL, ": not a valid identifier", ft_strchr(var, '='));
		free(var);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	exp_op(char *var, char *value, int g_env1)
{
	int	i;

	i = 0;
	if (ft_strchr(var, '=') && !ft_isdigit(var[0]) && var[0] != '='
		&& !ft_isqt(var[0]) && var[0] != '$')
	{
		if (ft_strchr(var, '+'))
			return (append_expo(var));
		value = fetch_var(var, &i);
		if (op_not(var[i - 1]))
			return (export_error(value, var));
		g_env1 = get_env(value);
		if (g_env.env_var[g_env1] == NULL)
			g_env.env_var = new_env(var);
		else
			replace_env(g_env1, var);
		free(value);
	}
	else
	{
		free(var);
		return (error_print(NULL, "Error: No value given!", NULL));
	}
	free(var);
	return (EXIT_SUCCESS);
}
