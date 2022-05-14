#include "../../includes/mini_shell.h"

int	ft_isqt(char c)
{
	if (c == 34 || c == 39)
		return (c);
	return (0);
}

int	check_qte_str(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (ft_isqt(str[i]))
			{
				return (ft_isqt(str[i]));
			}
			i++;
		}
	}
	return (0);
}
