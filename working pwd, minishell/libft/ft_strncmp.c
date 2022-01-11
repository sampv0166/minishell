/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 03:10:43 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/17 15:39:18 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || (!*s1 && !*s2))
	{
		return (0);
	}
	while ((*s1 || *s2) && (i < n))
	{
		if (*s1 != *s2)
		{
			return (((unsigned char )*s1) - ((unsigned char )*s2));
		}
		s1++;
		s2++;
		i++;
	}
	return (0);
}
