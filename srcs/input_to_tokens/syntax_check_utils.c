#include "../../includes/mini_shell.h"

bool	token_contains_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

bool	is_token_redir(char *str)
{
	if (ft_strlen (str) == 2)
	{
		if (ft_strnstr(str, "<<", 2) || ft_strnstr(str, ">>", 2))
			return (true);
	}
	if (ft_strlen (str) == 1)
	{
		if (ft_strnstr(str, "<", 1) || ft_strnstr(str, ">", 1))
		{
			return (true);
		}
	}
	return (false);
}

bool	is_token_pipe(char *str)
{
	if (ft_strlen (str) == 1)
	{
		if (ft_strchr(str, '|'))
			return (true);
	}
	if (ft_strlen(str) > 1)
	{
		if (*str == '|')
			return (false);
	}
	return (true);
}

bool	is_special_charater_correct(char *str)
{
	if (ft_strlen (str) != 2)
	{
		if (ft_strnstr(str, "<<", 2) || ft_strnstr(str, ">>", 2))
			return (false);
	}
	if (ft_strlen (str) != 1)
	{
		if ((ft_strchr(str, '<') && !ft_strnstr(str, "<<", 2)) \
		|| (ft_strchr(str, '>') && !ft_strnstr(str, ">>", 2)) \
		|| (ft_strchr(str, '|') && !ft_strnstr(str, "||", 2)))
			return (false);
	}
	return (true);
}

int	check_pipe_conditions(char **tokens, int i)
{
	if (tokens[i] && tokens[i][0] == '|'
		&& tokens[i + 1] && tokens[i + 1][0] == '|')
		return (false);
	if (tokens[i] && tokens[i][0] == '>'
		&& tokens[i + 1] && tokens[i + 1][0] == '|')
		return (false);
	if (tokens[i] && tokens[i][0] == '|' && i == 0)
		return (false);
	return (0);
}
