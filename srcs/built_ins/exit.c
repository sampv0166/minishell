#include "../../includes/mini_shell.h"

extern t_env_var env;

<<<<<<< HEAD

// tests cases not working
// exit

=======
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
>>>>>>> e9e6a83c439c26cb1936e511ff8997034a5e6ef2

unsigned char ft_exit(char **str)
{
	unsigned char	c;
	int				i;
	int				stat_code;
	print_2d_array(str);
	c = 0;
	i = 1;
	stat_code = 0;
	while (str[i] != NULL)
	{
		if (isalpha(str[i][0]))
		{
			c = 255;
			break;
		}
		else if (is_sign(str[i][0]) || isdigit(str[i][0]))
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
