#include "../../includes/mini_shell.h"

extern t_env_var	env;

static void	ft_exit_print(char *str)
{
	// ft_putstr_fd("exit: ", 2);
	// if (str == NULL)
	// 	ft_putendl_fd("too many arguments", 2);
	// else
	// {
	// 	ft_putstr_fd(str, 2);
	// 	ft_putendl_fd(": numeric argument requred", 2);
	// }
}

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
		ft_exit_print(NULL);
		env.trigger = 0;
		return (1);
	}
	*c = ft_atoi(str);
	return (0);
}

static void	ft_exit_init(int *i, unsigned char *c)
{
	*i = 1;
	*c = env.stat_code;
}

unsigned char	ft_exit(char **str, int pipe)
{
	unsigned char	c;
	int				i;

	ft_exit_init(&i, &c);
	env.trigger = 1;
	while (str[i] != NULL)
	{
		if (is_rdr(str[i]) || !ft_strcmp(str[i], "|"))
			break;
		delimit_qtes(str[i]);
		if (i > 1 || is_sign(str[i][0]) || ft_isdigit(str[i][0]))
		{
			if (check_args(str[i], i, &c))
			{
				c = 1;
				break ;
			}
		}
		else if (ft_isalpha(str[i][0]) || ft_isqt(str[i][0]))
		{
			ft_exit_print(str[i]);
			c = 2;
			break ;
		}
		i++;
	}
	env.stat_code = c;
	if (env.trigger && pipe == 0)
	{
		ft_putnbr_fd(env.stat_code, 2);
		ft_putchar_fd('\n', 2);
		exit(env.stat_code);
		// printf("check\n");
	}
	return (c);
}
