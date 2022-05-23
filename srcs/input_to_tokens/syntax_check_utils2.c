/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:29:13 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:29:14 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

bool	is_token_syntax_valid(char **tokens)
{
	int	i;

	i = 0;
	if (tokens[i] && tokens[i][0] == '|')
		return (false);
	while (tokens && tokens[i] != NULL)
	{
		if (!token_contains_quote(tokens[i]))
		{
			if (tokens[i] && tokens[i + 1] == NULL)
			{
				if (is_token_redir(tokens[i]))
					return (false);
				if (!is_token_pipe(tokens[i]))
					return (false);
			}
			if (check_pipe_conditions(tokens, i))
				return (false);
			if (!is_special_charater_correct(tokens[i]))
				return (false);
		}
		i++;
	}
	return (true);
}
