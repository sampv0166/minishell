#include "../../includes/mini_shell.h"

extern t_env_var env;

char *fetch_echo(char *str, char **env_var)
{
	char *lk_up;
	int i;

	i = 0;
	lk_up = ft_strdup(str);
	lk_up = ft_strchr(lk_up, '$');
	++lk_up;
	while (lk_up[i] != ' ' && lk_up[i] != '\0')
		i++;
	lk_up[i] = '\0';
	i = 0;
	while (env_var[i] != NULL)
	{
		if (ft_strstr(env_var[i], lk_up))
			break;
		i++;
	}
	if (env_var[i] == NULL)
		return (NULL);
	lk_up = ft_strdup(ft_strstr(env_var[i], lk_up));
	;
	lk_up = ft_strchr(lk_up, '=');
	if (lk_up)
		lk_up++;
	return (lk_up);
}

static void print(char *str, char **env_var, int *qte)
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
		if ((str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '?')) && *qte == 34)
		{
			if (str[i + 1] == '?')
			{
				val = ft_itoa(env.stat_code);
				ft_putstr_fd(val, 1);
				free(val);
			}
			else if (ft_isalpha(str[i + 1]))
			{
				val = NULL;
				j = 0;
				cat = ft_strdup(str);
				while (str[i] != ' ' && str[i] != '\0' && str[i] != *qte)
				{
					cat[j] = str[i];
					i++;
					j++;
				}
				cat[j] = '\0';
				val = fetch_echo(cat, env_var);
				free (cat);
				if (val)
					ft_putstr_fd(val, 1);
			}
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

void echo(char **str, char **env_var)
{
	int i;
	t_flags flags;
	int qte;

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
			print(str[i], env_var, &qte);
			i++;
			if (str[i] != NULL)
				ft_putchar_fd(' ', 1);
		}
	}
	if (!flags.newl_flag)
		ft_putchar_fd('\n', 1);
}