#include "../../includes/mini_shell.h"

int	error_print(char *stat_code, char *print, char *str)
{
	if (stat_code != NULL)
		ft_putnbr_fd(g_env.stat_code, 2);
	if (str != NULL)
	{
		if (stat_code != NULL)
			ft_putchar_fd(' ', 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" : ", 2);
	}
	ft_putendl_fd(print, 2);
	return (EXIT_FAILURE);
}
