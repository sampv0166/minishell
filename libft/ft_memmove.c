/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:49:11 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/22 12:27:11 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t		i;

	i = 0;
	if (dest == src || !len)
		return (dest);
	if (src < dest)
	{
		while (i < len)
		{
			*((char *)dest + (len - 1)) = *((char *)src + (len - 1));
			len--;
		}
	}
	else
	{
		ft_memcpy(dest, src, len);
	}
	return (dest);
}
