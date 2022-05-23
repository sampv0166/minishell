/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delimit_qtes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:27:28 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:27:29 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	qt_op(int *trig, char *str, int *qte, int *k)
{
	if (!(*trig))
	{
		*trig = 1;
		*qte = str[*k];
	}
	else
	{
		*trig = 0;
		*qte = 0;
	}
	(*k)++;
}

static void	replace_char(char *tmp, char *str, int *j, int *k)
{
	tmp[*j] = str[*k];
	(*j)++;
	(*k)++;
}

static void	take_qte(int *qte, char *str, int *k, int *trig)
{
	*qte = ft_isqt(str[*k]);
	*trig = 1;
	(*k)++;
}

static void	parse_str_qte(char *str, char *tmp, int *qte)
{
	int	k;
	int	j;
	int	trig;

	k = 0;
	trig = 0;
	j = 0;
	while (str[k])
	{
		if (ft_isqt(str[k]))
		{
			if (ft_isqt(str[k]) == *qte)
				qt_op(&trig, str, qte, &k);
			else if (!(*qte))
				take_qte(qte, str, &k, &trig);
			else
				replace_char(tmp, str, &j, &k);
		}
		else
			replace_char(tmp, str, &j, &k);
	}
	tmp[j] = '\0';
}

void	delimit_qtes(char *str)
{
	int		qte;
	int		j;
	char	*tmp;

	tmp = NULL;
	qte = check_qte_str(str);
	j = 0;
	if (str != NULL)
	{
		if (qte)
		{
			qte = 0;
			tmp = strdup(str);
			parse_str_qte(str, tmp, &qte);
			j = 0;
			while (tmp[j])
			{
				str[j] = tmp[j];
				j++;
			}
			str[j] = '\0';
			free(tmp);
		}
	}
}
