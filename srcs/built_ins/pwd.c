#include "../../includes/mini_shell.h"

extern t_env_var	env;

int	pwd(char **str, char **env)
{
	int		i;
	char	*s;
	char	dir[1000];

	i = 0;
	while (str[i] != NULL)
	{
		if (is_rdr(str[i]))
			break;
		else if (!ft_strcmp(str[i], "|"))
			break;
		i++;
	}
	s = get_env_dollar("$PWD");
	if (s == NULL)
		s = ft_strdup(getcwd(dir, 1000));
	ft_putendl_fd(s, 1);
	free(s);
	return (0);
}
