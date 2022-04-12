#include "../../includes/mini_shell.h"
// #include <unistd.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>

extern t_env_var	env;

char	*fetch_pwd(char *str, char **env)
{
	char	*lk_up;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strstr(env[i], str))
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (env[i]);
	lk_up = ft_strchr(env[i], '=');
	++lk_up;
	return (lk_up);
}

int	pwd(char **str, char **env)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '>'))
			break ;
		else if (ft_strchr(str[i], '<'))
			break ;
		else if (ft_strchr(str[i], '|'))
			break ;
		i++;
	}
	s = ft_strdup(fetch_pwd("PWD", env));
	ft_putendl_fd(s, 1);
	free(s);
	return (0);
}
