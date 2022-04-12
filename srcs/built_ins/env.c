#include "../../includes/mini_shell.h"

extern t_env_var	env;

int	get_env(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(env.env_var[i]);
	while (env.env_var[i] != NULL)
	{
		if (ft_strstr(env.env_var[i], str))
		{
			j = 0;
			free(tmp);
			tmp = ft_strdup(env.env_var[i]);
			while (tmp[j] != '=' && tmp[j] != '\0')
				j++;
			tmp[j] = '\0';
			if (!ft_strcmp(tmp, str))
				break ;
		}
		i++;
	}
	free(tmp);
	return (i);
}

int	env_var(void)
{
	ft_putstr_2d(env.env_var);
	return (0);
}
