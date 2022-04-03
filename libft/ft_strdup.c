/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:29:26 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/04 08:49:20 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*ptr;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1 && s1[j])
	{
		ptr[i] = s1[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
