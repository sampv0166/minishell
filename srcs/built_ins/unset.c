#include "../../includes/mini_shell.h"

extern t_env_var env;

static char	*fetch_unset(char *str, char **env)
{
	int	i;
	char	*val;
	int		j;

	i = 0;
	j = 0;
	val = NULL;
	while (str[j] != '=' && str[j] != '\0')
		j++;
	str[j] = '\0';
	while (env[i] != NULL)
	{
		if (ft_strstr(env[i], str))
		{
			j = 0;
			if (val)
				free(val);
			val = ft_strdup(env[i]);
			while (val[j] != '=' && val[j] != '\0')
				j++;
			val[j] = '\0';
			if (!ft_strcmp(val, str))
				break;
		}
		i++;
	}
	if (val)
		free(val);
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
}

static void	elimination(char *str, char **env)
{
	char	*s;
	char	*var;
	int		i;
	int		index = 0;

	i = 0;
	if (fetch_unset(str, env))
	{
		s = ft_strdup(fetch_unset(str, env));
		while (env[index] != NULL)
		{
			if (!ft_strcmp(s, env[index]))
				break;
			index++;
		}
		if (env[index] != NULL)
		{
			i = index;
			while (env[i + 1] != NULL)
			{
				free(env[i]);
				env[i] = ft_strdup(env[i + 1]);
				i++;
			}
			env[i] = NULL;
		}
	}
}

static void	parser1(char *str)
{
	char	*tmp;
	int		qte;
	int		j;
	int		i;

	qte = 0;
	i = 0;
	j = 0;
	if (!ft_strchr(str, '|') || !ft_strchr(str, '>') || !ft_strchr(str, '<'))
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

int	unset(char **str, char **env)
{
	int	i;

	i = 1;

	while (str[i] != NULL)
	{
		parser1(str[i]);
		if (ft_strchr(str[i], '|') || ft_strchr(str[i], '>') || ft_strchr(str[i], '<'))
			break;
		elimination(str[i], env);
		i++;
	}
	return (0);
}
