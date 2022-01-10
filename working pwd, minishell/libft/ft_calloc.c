/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:53:14 by apila-va          #+#    #+#             */
/*   Updated: 2021/09/30 16:24:26 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memmory;

	memmory = (void *) malloc(size * count);
	if (memmory == NULL)
		return (NULL);
	ft_bzero(memmory, size * count);
	return (memmory);
}
