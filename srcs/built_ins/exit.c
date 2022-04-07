#include "../../includes/mini_shell.h"

extern t_env_var env;


// tests cases not working
// exit

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
	
	c = 0;
	i = 1;
	stat_code = 0;
	while (str[i] != NULL)
	{
		if (ft_isalpha(str[i][0]))
		{
			c = 255;
			break;
		}
		else if (is_sign(str[i][0]) || ft_isdigit(str[i][0]))
		{
			if (i > 1)
			{
				c = 1;
				printf("exit: too many arguments\n");
				break;
			}
			stat_code = ft_atoi(str[i]);
			c = stat_code;
		}
		i++;
	}
	return (c);
}
