#include "../../includes/mini_shell.h"

extern t_env_var env;

static int	is_sign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	int	alpha;

	alpha = 1;
	if (c < '0')
		alpha = 0;
	else if (c > '9')
		alpha = 0;
	return (alpha);
}

unsigned char ft_exit(char **str)
{
	unsigned char	c;
	int				i;
	int				stat_code;
	char			*tmp;
	int				qte;
	int				j;
	int				k;
	
	c = 0;
	k = 0;
	qte = 0;
	tmp = NULL;
	i = 1;
	j = 0;
	stat_code = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == 34 || str[i][0] == 39)
			qte = str[i][0];
		if (qte)
		{
			j = 0;
			tmp = ft_strdup(str[i]);
			k = 0;
			while (tmp[k])
			{
				if (tmp[k] != qte)
				{
					str[i][j] = tmp[k];
					j++;
				}
				k++;
			}
			str[i][j] = '\0';
			free(tmp);
		}
		if (i > 1 || is_sign(str[i][0]) || ft_isdigit(str[i][0]))
		{
			if (i > 1)
			{
				c = 1;
				ft_putendl_fd("exit: too many arguments", 1);
				break;
			}
			stat_code = ft_atoi(str[i]);
			c = stat_code;
		}
		else if (ft_isalpha(str[i][0]))
		{
			ft_putstr_fd("exit: ", 1);
			ft_putstr_fd(str[i], 1);
			ft_putendl_fd(": numeric argument requred", 1);
			c = 255;
			break;
		}
		i++;
	}
	return (c);
}
