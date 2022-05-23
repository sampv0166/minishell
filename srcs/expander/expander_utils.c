/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:29:24 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:29:25 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*get_stat_code(char *res, char *tmp, t_expand *flags)
{
	char	*cat;

	flags->k += 2;
	cat = ft_itoa(g_env.stat_code);
	res = ft_strjoin(res, cat);
	free(cat);
	res = str_cpy(res, tmp, flags);
	return (res);
}

char	*expansion_for_str(char *str, t_expand *flags)
{
	char	*dol;
	char	*cat;
	int		j;

	j = 0;
	cat = ft_strdup(str);
	++j;
	while (ft_isenv(cat[j]))
		j++;
	cat[j] = '\0';
	if (ft_isdigit(str[1]))
		flags->k += 2;
	else
		flags->k += ft_strlen(cat);
	j = get_env(&cat[1]);
	if (g_env.env_var[j] != NULL)
	{
		dol = get_env_dollar(cat);
		if (!flags->trig)
			dol = value_exp(dol);
		free(cat);
		return (dol);
	}
	free(cat);
	return (NULL);
}

char	*get_dir(char *res, char *tmp, t_expand *flags)
{
	char	*dol;

	dol = getting_tild();
	res = ft_strjoin(res, dol);
	free(dol);
	res = str_cpy(res, tmp, flags);
	return (res);
}

char	*parse_for_stat_exp(char *tmp, char *res, t_expand *flags)
{
	char	*res1;

	res1 = NULL;
	if (tmp[flags->k + 1] == '?')
		res = get_stat_code(res, tmp, flags);
	else
	{
		res1 = expansion_for_str(&tmp[flags->k], flags);
		if (res1 != NULL)
		{	
			res = ft_strjoin(res, res1);
			free(res1);
			res = str_cpy(res, tmp, flags);
		}
	}
	return (res);
}

char	*get_tild(char *res, char *tmp, t_expand *flags)
{
	flags->k++;
	res = get_dir(res, tmp, flags);
	return (res);
}
