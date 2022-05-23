/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:29:26 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:29:27 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_init_exp(t_expand *flags)
{
	flags->i = 0;
	flags->k = 0;
	flags->qte = 0;
	flags->trig = 0;
}

char	*getting_tild(void)
{
	char	*pwd;
	char	s[1000];
	char	*ret;

	ret = NULL;
	pwd = ft_strdup(getcwd(s, 1000));
	ch_tild();
	ret = ft_strdup(getcwd(s, 1000));
	ch_home();
	chdir(pwd);
	free(pwd);
	return (ret);
}

void	qte_enc(char c, t_expand *flags)
{
	if (ft_isqt(c))
	{
		if (flags->trig == 1 && flags->qte == ft_isqt(c))
		{
			flags->qte = 0;
			flags->trig = 0;
		}
		else if (!(flags->qte))
		{
			flags->trig = 1;
			flags->qte = ft_isqt(c);
		}
	}
}

char	*value_exp(char *dol)
{
	char	**ptr;
	int		i;

	i = 1;
	ptr = ft_split(dol, ' ');
	free(dol);
	dol = ft_strdup(ptr[0]);
	while (ptr[i])
	{
		dol = ft_strjoin(dol, " ");
		dol = ft_strjoin(dol, ptr[i]);
		i++;
	}
	free_2d_array(ptr);
	return (dol);
}

char	*str_cpy(char *res, char *tmp, t_expand *flags)
{
	char	*cat;

	cat = ft_strdup(res);
	free(res);
	res = ft_calloc(ft_strlen(cat) + ft_strlen(tmp)
			- flags->k + 1, sizeof(char));
	flags->i = 0;
	while (cat[flags->i])
	{
		res[flags->i] = cat[flags->i];
		flags->i++;
	}
	res[flags->i] = 0;
	free(cat);
	return (res);
}
