/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:31:31 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/18 01:38:59 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*position;

	position = lst;
	while (position != NULL && position->next != NULL)
	{
		position = position->next;
	}
	return (position);
}
