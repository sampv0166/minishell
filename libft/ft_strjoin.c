/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 03:18:18 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/17 16:21:56 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	char	*ptr;
	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (newstr == NULL)
		return (NULL);		
	ptr = newstr;
	while (s1 && *s1)
	{
		*newstr = *s1;
		s1++;
		newstr++;
	}
	while (s2 && *s2)
	{
		*newstr = *s2;
		s2++;
		newstr++;
	}
	*newstr = '\0';
	return (ptr);
}
