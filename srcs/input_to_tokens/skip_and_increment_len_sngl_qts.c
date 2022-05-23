/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_and_increment_len_sngl_qts.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:28:50 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:28:51 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/*
    ! why this function ?  
    skip characters untill we encounter the next single quote and increment len
    
    !expected input : char *str , int i, int len   
    
    !return values
    returns 0 if there is no closing qutoe
    returns 1 if there is a closing quote
*/

static void	skip_and_increment_len_sngl_qts1(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
}

static void	skip_and_increment_len_sngl_qts2(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	if (str[*i] == '\"')
		(*i)++;
}

static int	skip_and_increment_len_sngl_qts3(int *len)
{
	(*len)++;
	return (0);
}

int	skip_and_increment_len_sngl_qts(char *str, int *i, int *len)
{
	(*i)++;
	if (str[*i] && ft_strchr_2(str + *i, '\''))
	{
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		if (str[*i] == '\'')
			(*i)++;
		while (str[*i])
		{
			if (str[*i] == ' ' || str[*i] == '>'
				|| str[*i] == '<' || str[*i] == '|')
				break ;
			else if (str[*i] == '\'')
				skip_and_increment_len_sngl_qts1(str, i);
			else if (str[*i] == '\"')
				skip_and_increment_len_sngl_qts2(str, i);
			else
				(*i)++;
		}
		(*len)++;
	}
	else
		return (skip_and_increment_len_sngl_qts3(len));
	return (1);
}
