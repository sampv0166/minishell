#include "../../includes/mini_shell.h"

extern t_env_var env;

char *fetch_echo(char *str)
{
	char *lk_up;
	char	*tmp;
	int i;
	int	j;

	i = 0;
	tmp = ft_strdup(env.env_var[i]);
	lk_up = ft_strdup(str);
	while (ft_isenv(lk_up[i]))
		i++;
	lk_up[i] = '\0';
	i = 0;
	while (env.env_var[i] != NULL)
	{
		if (ft_strstr(env.env_var[i], lk_up))
		{
			free(tmp);
			tmp = ft_strdup(env.env_var[i]);
			j = 0;
			while (tmp[j] != '=' && tmp[j] != '\0')
				j++;
			tmp[j] = '\0';
			if (!ft_strcmp(tmp, lk_up))
				break;
		}
		i++;
	}
	free(tmp);
	if (env.env_var[i] == NULL)
		return (NULL);
	lk_up = ft_strdup(ft_strstr(env.env_var[i], lk_up));
	lk_up = ft_strchr(lk_up, '=');
	if (lk_up)
		lk_up++;
	return (lk_up);
}

static void print(char *str, int *qte)
{
	int i;
	char *val;
	char	*cat;
	int	j;

	i = 0;
	cat = NULL;
	j = 0;
	if (!(*qte))
		*qte = 34;
	while (str[i])
	{
		if ((str[i] == '$' && (ft_isenv(str[i + 1]) || str[i + 1] == '?')) && *qte == 34)
		{
			if (str[i + 1] == '?')
			{
				val = ft_itoa(env.stat_code);
				ft_putstr_fd(val, 1);
				free(val);
				i += 2;
			}
			else if (ft_isenv(str[i + 1]))
			{
				val = NULL;
				j = 0;
				i += 1;
				cat = ft_strdup(str);
				while (ft_isenv(str[i]))
				{
					cat[j] = str[i];
					i++;
					j++;
				}
				cat[j] = '\0';
				ft_putstr_fd(cat, 1);
			}
			while (ft_isenv(str[i]))
				++i;
		}
		else
		{
			if (!(!i && str[i] == *qte) && !(str[i + 1] == '\0' && str[i] == *qte))
				ft_putchar_fd(str[i], 1);
			// else if (str[i] == *qte)
			// {
			// 	if (i > 0 && str[i + 1] != '\0')
			// 		ft_putchar_fd(str[i], 1);
			// }
			++i;
		}
	}
}

static int n_flag_cmp(char **str, t_flags *flags)
{
	int i;
	int j;

	i = 1;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j])
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

void echo(char **str)
{
	int i;
	t_flags flags;
	int qte;
	int	print_f;


	i = 1;
	print_f = 0;
	qte = 0;
	flags.newl_flag = 0;
	if (str[i])
	{
		i = n_flag_cmp(str, &flags);
		while (str[i] != NULL)
		{
			print_f = 0;
			if (str[i][0] == 39 || str[i][0] == 34)
				qte = str[i][0];
			if (ft_strchr(str[i], '>') || ft_strchr(str[i], '<') || ft_strchr(str[i], '|'))
			{
				if (ft_strchr(str[i], '>'))
				{
					if (!ft_strcmp(str[i], ">") || !ft_strcmp(str[i], ">>"))
					{
						print_f = 1;
						break;
					}
				}
				else if (ft_strchr(str[i], '<'))
				{
					if (!ft_strcmp(str[i], "<") || !ft_strcmp(str[i], "<<"))
					{
						print_f = 1;
						break;
					}
				}
				else if (ft_strchr(str[i], '|'))
				{
					if (!ft_strcmp(str[i], "|"))
					{
						print_f = 1;
						break;
					}
				}
			}
			if (!print_f)
				print(str[i], &qte);
			i++;
			if (str[i] != NULL)
				ft_putchar_fd(' ', 1);
		}
	}
	if (!flags.newl_flag)
		ft_putchar_fd('\n', 1);
}