#include "../../../includes/mini_shell.h"

extern t_env_var	env;

void	ft_exit_init(int *i, unsigned char *c)
{
	*i = 1;
	*c = env.stat_code;
	env.trigger = 0;
}

unsigned char	set_exit_triggers(unsigned char *c,
		int pipe, int *i, char **str)
{
	unsigned char	ret;

	ret = 0;
	env.stat_code = *c;
	if (env.trigger && pipe == 0)
		env.trigger = 1;
	else if (pipe != 0)
		env.trigger = 0;
	if ((*i) == 1 && str[*i] == NULL)
	{
		if (pipe)
		{
			*c = 0;
			env.trigger = 0;
		}
		else
			env.trigger = 1;
	}
	ret = *c;
	return (ret);
}
