#include "../../includes/mini_shell.h"

extern t_env_var	env;

static void	elimination(char *str)
{
	char	*s;
	int		i;
	int		index;

	i = 0;
	index = 0;
	s = ft_strdup(env.env_var[0]);
	i = get_env(str);
	index = i;
	if (env.env_var[index] != NULL)
	{
		i = index;
		while (env.env_var[i + 1] != NULL)
		{
			free(env.env_var[i]);
			env.env_var[i] = ft_strdup(env.env_var[i + 1]);
			i++;
		}
		free(env.env_var[i]);
		env.env_var[i] = NULL;
	}
	free(s);
}

static void	parse_unset(char *str)
{
	char	*tmp;
	int		qte;
	int		j;
	int		i;

	qte = 0;
	i = 0;
	j = 0;
	if (!is_rdr(str))
	{
		tmp = ft_strdup(str);
		if (str[0] == 39 || str[0] == 34)
			qte = str[0];
		while (str[i] != '=' && str[i] != '\0')
		{
			if (str[i] != qte)
			{
				tmp[j] = str[i];
				j++;
			}
			i++;
		}
		tmp[j] = '\0';
		j = 0;
		while (tmp[j])
		{
			str[j] = tmp[j];
			j++;
		}
		str[j] = '\0';
		free(tmp);
	}
}

int	unset(char **str)
{
	int	i;

	i = 1;

	while (str[i] != NULL)
	{
		parse_unset(str[i]);
		if (is_rdr(str[i]))
			break;
		elimination(str[i]);
		i++;
	}
	return (0);
}
