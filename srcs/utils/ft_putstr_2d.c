#include "../../includes/mini_shell.h"

void	ft_putstr_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_putendl_fd(str[i], 1);
		i++;
	}
}
