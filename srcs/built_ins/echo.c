#include "../../includes/mini_shell.h"

extern t_env_var env;

static void	ft_init(t_flags *flags)
{
	flags->newl_flag = 0;
}
static void	execution(t_flags *flags, char **str)
{
	if (!flags->newl_flag)
		ft_putstr_fd("\n", 1);
	// free_all(str);
}

char	*fetch_echo(char *str, char **env)
{
	char	*lk_up;
	int		i;

	i = 0;
	lk_up = ft_strdup(str);
	lk_up = ft_strchr(lk_up, '$');
	++lk_up;
	while (lk_up[i] != ' ' && lk_up[i] != '\0')
		i++;
	lk_up[i] = '\0';
	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], lk_up))
			break;
		i++;
	}
	lk_up = ft_strdup(ft_strstr(env[i], lk_up));
	if (!lk_up)
		return (lk_up);
	lk_up = ft_strchr(lk_up, '=');
	if (lk_up)
		lk_up++;
	return (lk_up);
}

static void	print(char *str, char **env, int *qte)
{
	int	i;

	i = 0;
	if (!(*qte))
		*qte = 34;
	while (str[i])
	{
		if (str[i] == '$' && *qte == 34)
		{
			// if (str[i + 1] == '?')
			// 	ft_putstr_fd(ft_itoa())
			ft_putstr_fd(fetch_echo(&str[i], env), 1);
			while (str[i] != ' ' && str[i] != '\0')
				++i;
		}
		else
		{
			if (!(!i && str[i] == *qte) && !(str[i + 1] == '\0' && str[i] == *qte))
				ft_putchar_fd(str[i], 1);
			++i;
		}
	}
}

static int	n_flag_cmp(char **str, t_flags *flags)
{
	int	i;
	int	j;

	i = 1;
	while (str[i] != NULL)
	{
		j = 0;
		while(str[i][j])
		{
			if (str[i][j] == '-' && !j)
			{
				j++;
				while (str[i][j] == 'n')
					j++;
				if (str[i][j] != '\0')
					return (i);
				flags->newl_flag = 1;
			}
			else
				return (i);
		}
		i++;
	}
	return (i);
}

void	echo(char **str, char **env)
{
	int		i;
	t_flags	flags;
	int		qte;

	i = 1;
	qte = 0;
	flags.newl_flag = 0;
	if (str[i])
	{
		i = n_flag_cmp(str, &flags);
		while (str[i] != NULL)
		{
			if (str[i][0] == 39 || str[i][0] == 34)
				qte = str[i][0];
			if (ft_strchr(str[i], '>') || ft_strchr(str[i], '<') || ft_strchr(str[i], '|'))
				break;
			print(str[i], env, &qte);
			i++;
			if (str[i] != NULL)
				ft_putchar_fd(' ', 1);
		}
	}
	if (!flags.newl_flag)
		ft_putchar_fd('\n', 1);
}