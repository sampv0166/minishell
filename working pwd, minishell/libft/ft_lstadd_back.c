/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:40:28 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/18 01:34:17 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*position;

	position = *lst;
	if (!lst || !new)
		return ;
	if (position == NULL)
	{
		*lst = new;
	}
	else
	{
		while (position->next != NULL)
		{
			position = position->next;
		}
		position->next = new;
	}
}
