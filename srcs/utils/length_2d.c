#include "../../includes/mini_shell.h"

extern t_env_var	env;

int	length_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}
