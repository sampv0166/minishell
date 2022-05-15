#include "../../../includes/mini_shell.h"

extern t_env_var	env;

static void	export_split_env(char *str)
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

static void	export_append(char *str, char *var, int g_env)
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

static int	plus_export(char *str)
{
	char	*var;
	int		g_env;
	int		i;

	i = 0;
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

static int	append_expo(char *var)
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
		// printf("%s: not a valid identifier\n", ft_strchr(var, '='));
		free(var);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	exp_op(char *var, char *value, int g_env)
{
	int	i;

	i = 0;
	if (ft_strchr(var, '=') && !ft_isdigit(var[0])
		&& !ft_isqt(var[0]) && var[0] != '$')
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
		// printf("%s: not a valid identifier\n", var);
		free(var);
		return (EXIT_FAILURE);
	}
	free(var);
	return (EXIT_SUCCESS);
}
