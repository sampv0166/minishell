#include "../../includes/mini_shell.h"

extern t_env_var env;

int	length_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

char	**trimmer(void)
{
	int		i;
	char	**trim;
	int		length;
	int		k;

	i = 0;
	k = 0;
	length = length_2d(env.env_var);
	trim = (char **)malloc(sizeof(char *) * (length + 1));
	while (env.env_var[i] != NULL)
	{
		k = 0;
		trim[i] = ft_strdup(env.env_var[i]);
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
	int		i;

	i = 0;
	while (trim[i + 1] != NULL)
	{
		if (ft_strcmp(trim[i], trim[i + 1]) > 0)
		{
			temp = ft_strdup(trim[i]);
			free(trim[i]);
			trim[i] = ft_strdup(trim[i + 1]);
			free(trim[i + 1]);
			trim[i + 1] = ft_strdup(temp);
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

void	ordered_string(char **trim)
{
	int	i;
	int	g_env;

	i = 0;
	g_env = 0;
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
		g_env = get_env(trim[i]);
		free(trim[i]);
		trim[i] = ft_strdup(env.env_var[g_env]);
		i++;
	}
}

static void	free_all(char **str)
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
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	str_len = 0;
	tmp = NULL;
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
		final[i] = ft_calloc(ft_strlen(value[i]) + 3, sizeof(char));
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
		if (!ft_strcmp(var[i], "OLDPWD"))
			trigger = 1;
		i++;
	}
	i = 0;
	while (final[i] != NULL)
	{
		res[i] = ft_strdup("declare -x ");
		if (!trigger && (var[i][0] == 'P'))
		{
			res[i] = ft_strjoin(res[i], "OLDPWD=\"\"");
			trigger = 1;
			i++;
			res[i] = ft_strdup("declare -x ");
		}
		res[i] = ft_strjoin(res[i], var[i]);
		res[i] = ft_strjoin(res[i], final[i]);
		i++;
	}
	res[i] = NULL;
	free_all(final);
	free_all(value);
	free_all(var);
	return (res);
}
char	**new_env(char *str)
{
	char	**new;
	int		length;
	int		i;

	length = 0;
	i = 0;
	while (env.env_var[length] != NULL)
		length++;
	new = (char **)malloc(sizeof(char *) * (length + 2));
	while(env.env_var[i] != NULL)
	{
		new[i] = ft_strdup(env.env_var[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	i++;
	new[i] = NULL;
	free_all(env.env_var);
	return (new);
}

int	plus_export(char *str)
{
	char	*tmp;
	char	*var;
	int		g_env;
	int		i;
	int		len;
	int		trig;

	i = 0;
	trig = 0;
	tmp = NULL;
	len = 0;
	g_env = 0;
	var = ft_strdup(str);
	while (var[i] != '+')
		i++;
	var[i] = '\0';
	if (var[0] == '$')
	{
		g_env = get_env(&var[1]);
		if (env.env_var[g_env] != NULL)
		{
			tmp = get_env_dollar(var);
			g_env = get_env(tmp);
			if (env.env_var[g_env] == NULL)
			{
				i = 0;
				while (var[i] != '=')
					i++;
				tmp = ft_strjoin(tmp, &var[i]);
				free(var);
				var = ft_strdup(tmp);
				trig = 1;
				free(env.env_var[g_env]);
				env.env_var[g_env] = ft_strdup(var);
			}
			else
			{
				i = 0;
				while (var[i] != '=')
					i++;
				++i;
				free(tmp);
				tmp = ft_strdup(env.env_var[g_env]);
				tmp = ft_strjoin(tmp, &var[i]);
				free(env.env_var[g_env]);
				env.env_var[g_env] = ft_strdup(tmp);
			}
			free(var);
			free(tmp);
			return (0);
		}
		else
		{
			printf("%s: not a valid identifier\n", ft_strchr(str, '='));
			free(var);
			return (1);
		}
	}
	g_env = get_env(var);
	if (env.env_var[g_env] == NULL)
	{
		free(var);
		var = ft_strdup(str);
		i = 0;
		while (var[i] != '+')
			i++;
		var[i] = '\0';
		len = ft_strlen(str);
		tmp = ft_calloc(1, len + 1);
		i = 0;
		while (str[i] != '=' && str[i] != '\0')
			i++;
		len = 0;
		while (str[i])
		{
			tmp[len] = str[i];
			len++;
			i++;
		}
		tmp[len] = '\0';
		var = ft_strjoin(var, tmp);
		free(tmp);
		env.env_var = new_env(var);
		free(var);
	}
	else
	{
		free(var);
		len = ft_strlen(str);
		tmp = ft_calloc(1, len + 1);
		i = 0;
		while (str[i] != '=' && str[i] != '\0')
			i++;
		++i;
		len = 0;
		while (str[i])
		{
			tmp[len] = str[i];
			len++;
			i++;
		}
		tmp[len] = '\0';
		var = ft_strdup(env.env_var[g_env]);
		var = ft_strjoin(var, tmp);
		free(env.env_var[g_env]);
		env.env_var[g_env] = ft_strdup(var);
		free(var);
		free(tmp);
	}
	return (0);
}

static char	*delimit_qte(char *str)
{
	char	*ret;
	int		qte;
	int		i;
	int		len;
	int		j;

	qte = 0;
	len = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			len++;
			qte = str[i];
		}
		i++;
	}
	if (!qte)
	{
		ret = ft_strdup(str);
		return(ret);
	}
	else
	{
		i = ft_strlen(str);
		ret = ft_calloc(1, i + 1 - len);
		i = 0;
		while (str[i])
		{
			if (str[i] != qte)
			{
				ret[j] = str[i];
				j++;
			}
			i++;
		}
		ret[j] = '\0';
		free(str);
	}
	return(ret);
}

int	op_not(char c)
{
	if (c == '=')
		return (1);
	else if (c == '+')
		return (1);
	else if (c == '/')
		return (1);
	else if (c == '*')
		return (1);
	else if (c == '-')
		return (1);
	else if (c == '%')
		return (1);
	return (0);
}

int	export_env(char *str)
{
	int	i;
	int		g_env;
	char	*var;
	char	*value;
	int		ret;
	char	*tmp;
	int		len;
	int		trig;

	i = 0;
	trig = 0;
	ret = 0;
	len = 0;
	g_env = 0;
	tmp = NULL;
	var = delimit_qte(str);
	len = ft_strlen(var);
	value = ft_calloc(1, len + 1);
	if (ft_isenv(var[0]) || var[0] == '$')
	{
		if (ft_strchr(var, '='))
		{
			if (ft_strchr(var, '+'))
			{
				while (var[i] != '+')
					i++;
				if (var[i + 1] == '=' && !op_not(var[i - 1]))
				{
					free(value);
					ret = plus_export(var);
					free(var);
					return(ret);
				}
				else
				{
					free(value);
					printf("%s: not a valid identifier\n", ft_strchr(var, '='));
					free(var);
					return (1);
				}

			}
			i = 0;
			while (var[i])
			{
				if (var[i] == '=')
					break;
				value[i] = var[i];
				i++;
			}
			if (op_not(var[i - 1]))
			{
				free(value);
				printf("%s: not a valid identifier\n", ft_strchr(var, '='));
				free(var);
				return (1);
			}
			value[i] = '\0';
			if (value[0] == '$')
			{
				g_env = get_env(&value[1]);
				if (env.env_var[g_env] != NULL)
				{
					tmp = get_env_dollar(value);
					g_env = get_env(tmp);
					i = 0;
					while (var[i] != '=')
						i++;
					tmp = ft_strjoin(tmp, &var[i]);
					free(var);
					var = ft_strdup(tmp);
					trig = 1;
					free(tmp);
				}
				else
				{
					free(value);
					printf("%s: not a valid identifier\n", ft_strchr(var, '='));
					free(var);
					return (1);
				}
			}
			if (!trig)
				g_env = get_env(value);
			if (env.env_var[g_env] == NULL)
				env.env_var = new_env(var);
			else
			{
				free(env.env_var[g_env]);
				env.env_var[g_env] = ft_strdup(var);
			}
		}
		else
		{
			free(value);
			printf("%s: not a valid identifier\n", ft_strchr(var, '='));
			free(var);
			return (1);
		}
	}
	else
	{
		free(value);
		printf("%s: not a valid identifier\n", ft_strchr(var, '='));
		free(var);
		return (1);
	}
	free(var);
	free(value);
	return (0);
}

int	export(char **str)
{
	char	**trim;
	char	**res;
	int		ret;
	int		i;

	i = 0;
	if (str[1] == NULL || is_rdr(str[1]) || !ft_strcmp(str[1], "|"))
	{
		trim = trimmer();
		sorting(trim);
		ordered_string(trim);
		res = declare_s(trim);
		print_2d_array(res);
		free_all(trim);
		free_all(res);
	}
	else
	{
		i = 1;
		while (str[i] != NULL)
		{
			if (is_rdr(str[i]) || !ft_strcmp(str[i], "|"))
				break;
			ret = export_env(str[i]);
			i++;
		}
		return(ret);
	}
	return (EXIT_SUCCESS);
}