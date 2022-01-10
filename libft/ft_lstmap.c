/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:23:49 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/18 01:40:23 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*element;
	t_list	*newlist;

	newlist = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		element = ft_lstnew(f(lst->content));
		if (!element)
		{
			ft_lstclear(&newlist, del);
			return (0);
		}
		ft_lstadd_back(&newlist, element);
		lst = lst->next;
	}
	return (newlist);
}
