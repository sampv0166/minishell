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

char	*free_memmory(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char	*ft_strjoin(char *saved_line, char *buffer)
{
	char	*new_string;
	int		total_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	total_len = ft_strlen(saved_line) + ft_strlen(buffer) + 1;
	new_string = (char *) malloc(sizeof(char) * (total_len));
	if (new_string == NULL)
		return (free_memmory(&new_string));
	while (saved_line && saved_line[i])
		new_string[i++] = saved_line[j++];
	j = 0;
	while (buffer && buffer[j])
		new_string[i++] = buffer[j++];
	new_string[i] = '\0';
	if (saved_line)
		free_memmory(&saved_line);
	return (new_string);
}
