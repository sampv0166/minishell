#include "../../../includes/mini_shell.h"

extern t_env_var	env;

int	export_env(char *str)
{
	char	*var;
	char	*value;

	delimit_qtes(str);
	var = ft_strdup(str);
	value = NULL;
	if (exp_op(var, value, 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	export(char **str)
{
	int		ret;
	int		i;

	i = 0;
	if (str[1] == NULL || is_rdr(str[1]) || !ft_strcmp(str[1], "|"))
		exp_one_arg();
	else
	{
		i = 1;
		while (str[i] != NULL)
		{
			if (is_rdr(str[i]) || !ft_strcmp(str[i], "|"))
				break ;
			ret = export_env(str[i]);
			i++;
		}
		return (ret);
	}
	return (EXIT_SUCCESS);
}
