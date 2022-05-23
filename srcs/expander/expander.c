/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:29:29 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:29:30 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	place_values(char *res, char *tmp, t_expand *flags)
{
	res[flags->i] = tmp[flags->k];
	flags->i++;
	flags->k++;
}

static int	check_exp(t_expand *flags, char *tmp)
{
	if (((flags->qte != 39 || g_env.here_doc) && (tmp[flags->k] == '$'
				&& tmp[flags->k + 1] == '?'))
		|| ((flags->qte != 39 || g_env.here_doc)
			&& (tmp[flags->k] == '$' && ft_isenv(tmp[flags->k + 1]))))
		return (1);
	return (0);
}

char	*parse_str(char	*tmp)
{
	t_expand	flags;
	char		*res;

	ft_init_exp(&flags);
	res = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
	while (tmp[flags.k])
	{
		if (ft_isqt(tmp[flags.k]))
			qte_enc(tmp[flags.k], &flags);
		res[flags.i] = '\0';
		if (check_exp(&flags, tmp))
			res = parse_for_stat_exp(tmp, res, &flags);
		else if (tmp[flags.k] == '$' && ft_isqt(tmp[flags.k + 1])
			&& !flags.trig)
			flags.k++;
		else if ((!flags.k || (flags.k > 0 && (tmp[flags.k - 1] != '$')))
			&& (tmp[flags.k] == '~' && (tmp[flags.k + 1] == '/'
					|| tmp[flags.k + 1] == '\0')) && !flags.qte)
			res = get_tild(res, tmp, &flags);
		else
			place_values(res, tmp, &flags);
	}
	res[flags.i] = '\0';
	return (res);
}
