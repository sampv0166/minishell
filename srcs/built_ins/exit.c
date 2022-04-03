#include "../../includes/mini_shell.h"

extern t_env_var env;

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
			c = 2;
			break;
		}
		else if (ft_isdigit(str[i][0]))
		{
			stat_code = ft_atoi(str[i]);
			c = stat_code;
		}
		i++;
	}
	env.stat_code = c;
	return (c);
}