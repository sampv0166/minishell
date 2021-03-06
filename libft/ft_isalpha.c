/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:36:12 by apila-va          #+#    #+#             */
/*   Updated: 2021/10/01 01:34:05 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int val)
{
	if ((val >= 'a' && val <= 'z') || (val >= 'A' && val <= 'Z'))
	{
		return (1);
	}
	return (0);
}
