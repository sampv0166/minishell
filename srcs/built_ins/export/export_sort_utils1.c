#include "../../../includes/mini_shell.h"

extern t_env_var	env;

static char	**trimmer(void)
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
		while (trim[i][k] != '=' && trim[i][k] != '\0')
			k++;
		trim[i][k] = '\0';
		i++;
	}
	trim[i] = NULL;
	return (trim);
}

char	**t_sort(char **trim)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (trim[i + 1][0] != 'T')
	{
		temp = ft_strdup(trim[i]);
		free(trim[i]);
		trim[i] = ft_strdup(trim[i + 1]);
		free(trim[i + 1]);
		trim[i + 1] = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (trim);
}

char	**sorting(char **trim)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
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
	trim = t_sort(trim);
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

void	exp_one_arg(void)
{
	char	**trim;
	char	**res;

	trim = trimmer();
	sorting(trim);
	ordered_string(trim);
	res = declare_s(trim);
	ft_putstr_2d(res);
	free_2d_array(trim);
	free_2d_array(res);
}
