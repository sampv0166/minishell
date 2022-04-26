#include "../../includes/mini_shell.h"

extern t_env_var	env;

/*Returning the index of the env varibale in fetching*/
int	get_env(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(env.env_var[i]);
	while (env.env_var[i] != NULL)
	{
		/*In this while loop I check for the first occurence of the string which I'm looking for in env varibale*/
		if (ft_strstr(env.env_var[i], str))
		{
			/*The moment it encounters any string I pass the value of index of env and check the variable if that variable matches with my str.
			In case if it doesn't match the loop is still on running until it matches the requirements or it reaches to the of NULL in env*/
			j = 0;
			free(tmp);
			tmp = ft_strdup(env.env_var[i]);
			while (tmp[j] != '=' && tmp[j] != '\0')
				j++;
			tmp[j] = '\0';
			if (!ft_strcmp(tmp, str))
				break ;
		}
		i++;
	}
	free(tmp);
	return (i);
}

/*Returning the str value of the env varibale in fetching*/
char	*get_env_dollar(char *str)
{
	int		i;
	int		j;
	int		g_env;
	char	*ret;
	char	*env_s;

	i = 0;
	j = 1;
	g_env = 0;
	ret = ft_strdup("1");
	if (str[j] == '?')
	{
		/*Fetch for exit codes*/
		free(ret);
		ret = ft_itoa(env.stat_code);
		return (ret);
	}
	else if (ft_isenv(str[j]))
	{
		/*This while loop to count how much memory we need for the environment variable which we're looking to fetch*/
		while (str[j] && ft_isenv(str[j]))
			j++;
		env_s = ft_calloc(sizeof(char), j + 1);
		j = 1;
		
		/*Allocation done and put values here*/
		while (str[j] && ft_isenv(str[j]))
		{
			env_s[j - 1] = str[j];
			j++;
		}
		env_s[j - 1] = '\0';

		/*Getting the index of the env variable*/
		g_env = get_env(env_s);
		free(env_s);
		if (env.env_var[g_env] != NULL)
		{
			i = 0;
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
				free(ret);
				
				/*Allocation and putting values of the env variable*/
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
