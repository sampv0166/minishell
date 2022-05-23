/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:29:16 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:29:17 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	**join_toks(char **tok1, char **tok2)
{
	int		len;
	char	**new_toks;
	int		i;
	int		j;

	len = (get_2d_arr_len2(tok1) + get_2d_arr_len2(tok2)) + 1;
	new_toks = malloc(sizeof(char *) * len + 1);
	i = 0;
	j = 0;
	while (tok1[i])
	{
		new_toks[i] = ft_strdup(tok1[i]);
		i++;
	}
	while (tok2[j])
	{
		new_toks[j + i] = ft_strdup(tok2[j]);
		j++;
	}
	new_toks[j + i] = NULL;
	ft_free_str_array(&tok1);
	ft_free_str_array(&tok2);
	return (new_toks);
}

char	*join_pipes(void)
{
	char	*in;
	char	*buf;

	in = NULL;
	buf = NULL;
	while (1)
	{
		if (read_buf(&buf, &in))
			return (NULL);
		in = ft_strjoin(in, buf);
		if (ft_strlen(in) > 0)
		{
			if (in[ft_strlen(in) - 1] == '|')
			{
				if (in && in[0] == '|')
					break ;
				continue ;
			}
			else
				break ;
		}
	}
	return (in);
}

char	**get_command_for_pipe(char **toks, char ***tokens, char *input)
{
	toks = split_to_tokens(input);
	*tokens = join_toks(*tokens, toks);
	free_me(&input);
	if (!is_token_syntax_valid(*tokens))
	{
		ft_free_str_array(tokens);
		ft_free_str_array(&toks);
		free_me(&input);
		return (NULL);
	}
	return (*tokens);
}

static void	error_syntax_qtes(int ret, char **tokens)
{
	if (ret)
	{
		ft_putstr_fd("Error: Quotes are not closed\n", 2);
		g_env.stat_code = 1;
	}
	else
	{
		ft_putstr_fd("Invalid Syntax\n", 2);
		g_env.stat_code = 258;
	}
	ft_free_str_array(&tokens);
}

char	**tokens_split(char *input)
{
	char	**tokens;
	char	**toks;
	int		ret;

	ret = 0;
	toks = NULL;
	tokens = split_to_tokens(input);
	ret = check_cmds_qtes(tokens);
	if (!tokens || !is_token_syntax_valid(tokens) || ret)
	{
		error_syntax_qtes(ret, tokens);
		return (NULL);
	}
	if (tokens[get_2d_arr_len(tokens)][0] == '|')
	{
		input = join_pipes();
		if (input)
			get_command_for_pipe(toks, &tokens, input);
		else
		{
			ft_free_str_array(&tokens);
			free_env();
		}
	}
	return (tokens);
}
