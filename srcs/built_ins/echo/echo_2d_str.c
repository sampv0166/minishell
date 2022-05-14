#include "../../../includes/mini_shell.h"

extern t_env_var	env;

static void	parse_str_splitted(char **str, int *i, char **str2)
{
	while (str[(*i)] != NULL)
	{
		if ((is_rdr(str[(*i)]) && is_rdr(str2[(*i)]))
			|| (!ft_strcmp(str[(*i)], "|")
				&& !ft_strcmp(str2[(*i)], "|")))
			break ;
		else
		{
			if (check_qte_str(str2[(*i)]))
				delimit_qtes(str[(*i)]);
		}
		(*i)++;
	}
}

static void	parse_str1(char **str, int *i)
{
	while (str[(*i)] != NULL)
	{
		if (is_rdr(str[(*i)]) || !ft_strcmp(str[(*i)], "|"))
			break ;
		else
		{
			if (check_qte_str(str[(*i)]))
				delimit_qtes(str[(*i)]);
		}
		(*i)++;
	}
}

int	parse_str_echo(char **str, char **str_splitted)
{
	int	i;

	i = 1;
	if (get_2d_arr_len2(str) == get_2d_arr_len2(str_splitted))
		parse_str_splitted(str, &i, str_splitted);
	else
		parse_str1(str, &i);
	return (i);
}