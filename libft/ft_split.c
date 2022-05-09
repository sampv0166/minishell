/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@42.abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 07:53:59 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/22 13:02:55 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
		}
		else if (s[i] != c)
		{
			while (s[i] && s[i] != c)
			{
				i++;
			}
			j++;
		}
	}
	return (j);
}

static char	**ft_create_string(char **ptr, char const *s, char c, size_t len)
{
	size_t	i;
	size_t	array_index;

	i = 0 ;
	array_index = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
			{
				i++;
				len++;
			}
			ptr[array_index++] = ft_substr(s, i - len, len);
			len = 0;
		}
		else
			i++;
	}
	ptr[array_index] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	first_array_length;
	size_t	string_length;

	string_length = 0;
	if (!s)
		return (0);
	first_array_length = ft_count(s, c);
	ptr = (char **)ft_calloc(sizeof (char *), (first_array_length + 1));
	if (!ptr)
		return (0);
	if (first_array_length <= 0)
	{
		ptr[0] = NULL;
		return (ptr);
	}
	ptr = ft_create_string(ptr, s, c, string_length);
	return (ptr);
}
