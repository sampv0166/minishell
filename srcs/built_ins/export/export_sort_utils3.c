#include "../../../includes/mini_shell.h"

extern t_env_var	env;

int	check_old_pwd(char **var)
{
	int	i;

	i = 0;
	while (var[i] != NULL)
	{
		if (!ft_strcmp(var[i], "OLDPWD"))
			return (1);
		i++;
	}
	return (0);
}