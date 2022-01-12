#include "../includes/mini_shell.h"

int cd(char *path) 
{
    return chdir(path);
}

void	echo(char **str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if (!ft_strcmp(str[i + 1], "-n"))
			i = 1;
		ft_putstr_fd(str[i + 1], 1);
		if (str[i + 2] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (ft_strcmp(str[1], "-n") || str[1] == NULL)
		ft_putchar_fd('\n', 1);
}