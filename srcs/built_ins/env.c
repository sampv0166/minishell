#include "../../includes/mini_shell.h"

extern t_env_var	env;

static char	*getting_var(char *str, int len)
{
	char	*env_s;

	env_s = NULL;
	while (str[len] && ft_isenv(str[len]))
		len++;
	env_s = ft_calloc(sizeof(char), len + 1);
	len = 1;
	/*Allocation done and put values here*/
	while (str[len] && ft_isenv(str[len]))
	{
		env_s[len - 1] = str[len];
		len++;
	}
	env_s[len - 1] = '\0';
	return (env_s);
}

static char	*getting_ret(int g_env, int i, int j)
{
	char	*ret;

	ret = NULL;
	ret = ft_calloc(sizeof(char), j + 1);
	i = i - j;
	j = 0;
	while (env.env_var[g_env][i])
	{
		ret[j] = env.env_var[g_env][i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

static char	*getting_value(int g_env)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	ret = NULL;
	j = 0;
	/*Iterating towards = sign*/
	while (env.env_var[g_env][i] != '=' && env.env_var[g_env][i] != '\0')
		i++;
	if (env.env_var[g_env][i] == '=')
	{
		++i;
		j = 0;
		/*Iterating towards \0 and counting all the characters with variable j*/
		while (env.env_var[g_env][i])
		{
			i++;
			j++;
		}
		/*Allocation and putting values of the env variable*/
		ret = getting_ret(g_env, i, j);
		return (ret);
	}
	return (NULL);
}

/*Returning the str value of the env varibale in fetching*/
char	*get_env_dollar(char *str)
{
	int		j;
	char	*ret;

	j = 1;
	ret = malloc(sizeof(char));
	if (str[j] == '?')
	{
		/*Fetch for exit codes*/
		free(ret);
		ret = ft_itoa(env.stat_code);
		return (ret);
	}
	else if (ft_isenv(str[j]))
	{
		free(ret);
		/*This while loop to count how much memory we need for the environment variable which we're looking to fetch*/
		ret = getting_var(str, j);
		/*Getting the index of the env variable*/
		if (env.env_var[get_env(ret)] != NULL)
		{
			j = get_env(ret);
			free(ret);
			ret = getting_value(j);
			return (ret);
		}
	}
	free(ret);
	return (NULL);
}

int	env_var(void)
{
	print_2d_array(env.env_var);
	return (0);
}
