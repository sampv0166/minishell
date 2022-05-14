#include "../../includes/mini_shell.h"

int	ft_isenv(char c)
{
	if (c == '_')
		return (1);
	else if (ft_isalpha(c))
		return (1);
	else if (ft_isdigit(c))
	{
		if (c == '+' || c == '-')
			return (0);
		return (1);
	}
	else if (c == '\\')
		return (1);
	return (0);
}
