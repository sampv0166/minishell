/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 02:43:45 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/20 11:58:21 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*ptr;

	if (!s || start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	substr = malloc(sizeof (char) * (len + 1));
	if (substr == NULL || s == NULL)
		return (NULL);
	ptr = substr;
	while (s[start] && len)
	{
		*substr = s[start];
		start++;
		len--;
		substr++;
	}
	*substr = '\0';
	return (ptr);
}
