/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:50 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:51 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

char	**new_env(char *str)
{
	char	**new;
	int		length;
	int		i;

	length = 0;
	i = 0;
	while (g_env.env_var[length] != NULL)
		length++;
	new = (char **)malloc(sizeof(char *) * (length + 2));
	while (g_env.env_var[i] != NULL)
	{
		new[i] = ft_strdup(g_env.env_var[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	i++;
	new[i] = NULL;
	free_2d_array(g_env.env_var);
	return (new);
}

void	export_new_env(char *var, char *tmp)
{
	var = ft_strjoin(var, tmp);
	free(tmp);
	g_env.env_var = new_env(var);
	free(var);
}

int	op_not(char c)
{
	if (c == '=')
		return (1);
	else if (c == '+')
		return (1);
	else if (c == '/')
		return (1);
	else if (c == '*')
		return (1);
	else if (c == '-')
		return (1);
	else if (c == '%')
		return (1);
	return (0);
}

char	*fetch_var(char *var, int *i)
{
	char	*value;

	value = ft_calloc(1, ft_strlen(var) + 1);
	*i = 0;
	while (var[*i])
	{
		if (var[*i] == '=')
			break ;
		value[*i] = var[*i];
		(*i)++;
	}
	value[(*i)] = '\0';
	return (value);
}

int	export_error(char *value, char *var)
{
	free(value);
	error_print(NULL, ": not a valid identifier", ft_strchr(var, '='));
	free(var);
	return (EXIT_FAILURE);
}
