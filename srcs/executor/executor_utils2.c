#include "../../includes/mini_shell.h"

extern t_env_var	env;

int	get_2d_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	if (i != 0)
		i = i - 1;
	return (i);
}

int	get_2d_arr_len2(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
