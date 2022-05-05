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

static char	*get_unset_env(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	i = 0;
	j = 0;
	tmp = ft_strdup(str);
	delimit_qtes(str);
	while (str[i] != '=' && str[i] != '\0')
	{
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

static void	parse_unset(char *str)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	j = 0;
	if (!is_rdr(str))
	{
		tmp = get_unset_env(str);
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
		if (env.pa_tkns->is_out || env.pa_tkns->pipe || env.pa_tkns->is_in || env.pa_tkns->is_out_appnd || env.pa_tkns->here_doc)
			break ;
		elimination(str[i]);
		i++;
	}
	return (0);
}
