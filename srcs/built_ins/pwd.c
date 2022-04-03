#include "../../includes/mini_shell.h"

extern t_env_var env;

char	*fetch_pwd(char *str, char **env)
{
	char	*lk_up;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strstr(env[i], str))
			break;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	lk_up = ft_strdup(ft_strchr(env[i], '='));
	++lk_up;
	return (lk_up);
}

int	pwd(char **str, char **env)
{
	int	i;
	char	*s;

	i = 0;
	while (!(*s) && str[i] != NULL)
	{
		if (ft_strchr(str[i], '>'))
			s = ft_strchr(str[i], '>');
		else if (ft_strchr(str[i], '<'))
			s = ft_strchr(str[i], '<');
		else if (ft_strchr(str[i], '|'))
			s = strchr(str[i], '|');
		if (*s)
			break;
		i++;
	}
	s = fetch_pwd("PWD", env);
	ft_putendl_fd(s, 1);
	return (0);
}