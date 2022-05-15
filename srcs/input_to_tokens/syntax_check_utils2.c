#include "../../includes/mini_shell.h"

bool	is_token_syntax_valid(char **tokens)
{
	int	i;

	i = 0;
	if (get_2d_arr_len2(tokens) == 1 && tokens[i] && tokens[i][0] == '|')
		return (false);
	while (tokens && tokens[i] != NULL)
	{
		if (!token_contains_quote(tokens[i]) && !(is_inbuilt(tokens[i])))
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
