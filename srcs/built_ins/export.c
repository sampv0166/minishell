#include "../../includes/mini_shell.h"

extern t_env_var env;

void	ft_putstr_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_putstr_fd(str[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	length_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

char	**trimmer(char **str)
{
	int		i;
	char	**trim;
	int		length;
	int		k;

	i = 0;
	k = 0;
	length = length_2d(str);
	trim = (char **)malloc(sizeof(char *) * (length + 1));
	while (str[i] != NULL)
	{
		k = 0;
		trim[i] = strdup(str[i]);
		while (trim[i][k] != '=')
			k++;
		trim[i][k] = '\0';
		i++;
	}
	trim[i] = NULL;
	return (trim);
}

char	**sorting(char **trim)
{
	char	*temp;
	int		index;
	int		i;

	i = 0;
	while (trim[i + 1] != NULL)
	{
		if (strcmp(trim[i], trim[i + 1]) > 0)
		{
			temp = ft_strdup(trim[i]);
			free(trim[i]);
			trim[i] = ft_strdup(trim[i + 1]);
			free(trim[i + 1]);
			trim[i + 1] = strdup(temp);
			free(temp);
			i = 0;
		}
		i++;
	}
	i = 0;
	while (trim[i + 1][0] != 'T')
	{
		temp = strdup(trim[i]);
		free(trim[i]);
		trim[i] = ft_strdup(trim[i + 1]);
		free(trim[i + 1]);
		trim[i + 1] = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (trim);
}

char	*fetch(char *str, char **env)
{
	char	*lk_up;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], str))
			break;
		i++;
	}
	lk_up = ft_strdup(ft_strstr(env[i], str));
	if (!lk_up)
		return (lk_up);
	free(str);
	return (lk_up);
}

void	ordered_string(char **trim, char **str)
{
	int	i;

	i = 0;
	while (trim[i] != NULL)
		i++;
	i -= 2;
	free(trim[i]);
	trim[i] = ft_strdup(trim[i + 1]);
	free(trim[i + 1]);
	trim[i + 1] = NULL;
	i = 0;
	while (trim[i] != NULL)
	{
		trim[i] = fetch(trim[i], str);
		i++;
	}
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**declare_s(char **str)
{
	int	i;
	char	**res;
	char	**value;
	char	**var;
	int		j;
	int		k;
	char	**final;
	int		trigger;
	int		str_len;

	i = 0;
	j = 0;
	k = 0;
	str_len = 0;
	trigger = 0;

	k = length_2d(str);
	var = (char **)malloc(sizeof(char *) * (k + 1));
	res = (char **)malloc(sizeof(char *) * (k + 2));
	value = (char **)malloc(sizeof(char *) * (k + 1));
	final = (char **)malloc(sizeof(char *) * (k + 1));
	while (str[i] != NULL)
	{
		j = 0;
		str_len = ft_strlen(str[i]);
		var[i] = malloc(sizeof(char) * (str_len + 1));
		while(str[i][j] != '=')
		{
			var[i][j] = str[i][j];
			j++;
		}
		var[i][j] = '\0';
		i++;
	}
	var[i] = NULL;
	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		k = 0;
		str_len = ft_strlen(str[i]);
		value[i] = malloc(sizeof(char) * (str_len + 1));
		while (str[i][j] != '=')
			j++;
		while (str[i][j])
		{
			value[i][k] = str[i][j];
			j++;
			k++;
		}
		value[i][k] = '\0';
		i++;
	}
	value[i] = NULL;
	i = 0;
	while (value[i] != NULL)
	{
		j = 0;
		k = 0;
		str_len = ft_strlen(value[i]);
		final[i] = ft_calloc(strlen(value[i]) + 3, sizeof(char));
		if (value[i][j] == '=')
		{
			final[i][k] = value[i][j];
			j++;
			k++;
			final[i][k] = 34;
			k++;
			while (value[i][j])
			{
				final[i][k] = value[i][j];
				k++;
				j++;
			}
			final[i][k] = 34;
			k++;
			final[i][k] = '\0';
			i++;
		}
	}
	final[i] = NULL;
	i = 0;
	while (var[i] != NULL)
	{
		if (!strcmp(var[i], "OLDPWD"))
			trigger = 1;
		i++;
	}
	i = 0;
	while (final[i] != NULL)
	{
		res[i] = ft_strdup("declare -x ");
		if (!trigger && (var[i][0] == 'P'))
		{
			res[i] = ft_strjoin(res[i], "OLDPWD");
			trigger = 1;
			i++;
			res[i] = ft_strdup("declare -x ");
		}
		res[i] = ft_strjoin(res[i], var[i]);
		if (strcmp(var[i], "OLDPWD"))
			res[i] = ft_strjoin(res[i], final[i]);
		i++;
	}
	res[i] = NULL;
	free_all(final);
	free_all(value);
	free_all(var);
	return (res);
}

int	export(char **str, char **env)
{
	char	**trim;
	char	**res;

	trim = trimmer(env);
	sorting(trim);
	ordered_string(trim, env);
	res = declare_s(trim);
	ft_putstr_2d(res);
	free_all(trim);
	free_all(res);
	return (EXIT_SUCCESS);
}