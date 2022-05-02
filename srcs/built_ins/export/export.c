#include "../../../includes/mini_shell.h"

extern t_env_var	env;

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
	while (env.env_var[i] != NULL)
	{
		new[i] = ft_strdup(env.env_var[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	i++;
	new[i] = NULL;
	free_2d_array(env.env_var);
	return (new);
}

void	export_new_env(char *var, char *tmp)
{
	var = ft_strjoin(var, tmp);
	free(tmp);
	env.env_var = new_env(var);
	free(var);
}

void	export_split_env(char *str)
{
	int		i;
	char	*var;
	char	*tmp;
	int		len;

	tmp = NULL;
	var = ft_strdup(str);
	i = 0;
	while (var[i] != '+')
		i++;
	var[i] = '\0';
	tmp = ft_calloc(1, ft_strlen(str) + 1);
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
	export_new_env(var, tmp);
}

void	export_append(char *str, char *var, int g_env)
{
	char	*tmp;
	int		i;
	int		len;

	tmp = ft_calloc(1, ft_strlen(str) + 1);
	len = 0;
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	++i;
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

int	plus_export(char *str)
{
	char	*tmp;
	char	*var;
	int		g_env;
	int		i;
	int		len;

	i = 0;
	tmp = NULL;
	len = 0;
	g_env = 0;
	var = ft_strdup(str);
	while (var[i] != '+')
		i++;
	var[i] = '\0';
	g_env = get_env(var);
	free(var);
	var = NULL;
	if (env.env_var[g_env] == NULL)
		export_split_env(str);
	else
		export_append(str, var, g_env);
	return (0);
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

int	append_expo(char *var)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (var[i] != '+')
		i++;
	if (var[i + 1] == '=' && !op_not(var[i - 1]))
	{
		ret = plus_export(var);
		free(var);
		return (ret);
	}
	else
	{
		printf("%s: not a valid identifier\n", ft_strchr(var, '='));
		free(var);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*fetch_var(char *var, int *i)
{
	char	*value;

	value = ft_calloc(1, ft_strlen(var) + 1);
	*i = 0;
	while (var[*i])
	{
		if (var[*i] == '=')
			break ;
		value[*i] = var[*i];
		(*i)++;
	}
	value[(*i)] = '\0';
	return (value);
}

int	export_error(char *value, char *var)
{
	free(value);
	printf("%s: not a valid identifier\n", ft_strchr(var, '='));
	free(var);
	return (EXIT_FAILURE);
}

void	replace_env(int g_env, char *var)
{
	free(env.env_var[g_env]);
	env.env_var[g_env] = ft_strdup(var);
}

int	exp_op(char *var, char *value, int g_env)
{
	int	i;

	i = 0;
	if (ft_strchr(var, '='))
	{
		if (ft_strchr(var, '+'))
			return (append_expo(var));
		value = fetch_var(var, &i);
		if (op_not(var[i - 1]) || (!var[i + 1]))
			return (export_error(value, var));
		g_env = get_env(value);
		if (env.env_var[g_env] == NULL)
			env.env_var = new_env(var);
		else
			replace_env(g_env, var);
		free(value);
	}
	else
	{
		printf("%s: not a valid identifier\n", var);
		free(var);
		return (EXIT_FAILURE);
	}
	free(var);
	return (EXIT_SUCCESS);
}

int	export_env(char *str)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	delimit_qtes(str);
	var = ft_strdup(str);
	value = NULL;
	if (exp_op(var, value, 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	export(char **str)
{
	int		ret;
	int		i;

	i = 0;
	if (str[1] == NULL || is_rdr(str[1]) || !ft_strcmp(str[1], "|"))
		exp_one_arg();
	else
	{
		i = 1;
		while (str[i] != NULL)
		{
			if (is_rdr(str[i]) || !ft_strcmp(str[i], "|"))
				break ;
			ret = export_env(str[i]);
			i++;
		}
		return (ret);
	}
	return (EXIT_SUCCESS);
}
