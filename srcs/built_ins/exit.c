#include "../../includes/mini_shell.h"

extern t_env_var	env;

static int	is_sign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

static int	check_args(char *str, int i, unsigned char *c)
{
	if (i > 1)
	{
		*c = 1;
		ft_putendl_fd("exit: too many arguments", 1);
		env.trigger = 1;
		return (1);
	}
	*c = ft_atoi(str);
	return (0);
}

unsigned char	ft_exit(char **str)
{
	unsigned char	c;
	int				i;

	c = 0;
	i = 0;
	env.trigger = 0;
	while (str[++i] != NULL)
	{
		delimit_qtes(str[i]);
		if (i > 1 || is_sign(str[i][0]) || ft_isdigit(str[i][0]))
		{
			if (check_args(str[i], i, &c))
				break ;
		}
		else if (ft_isalpha(str[i][0]))
		{
			ft_putstr_fd("exit: ", 1);
			ft_putstr_fd(str[i], 1);
			ft_putendl_fd(": numeric argument requred", 1);
			c = 255;
			break ;
		}
	}
	return (c);
}
