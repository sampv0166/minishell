#include "../../includes/mini_shell.h"

int	ft_isenv(char c)
{
	// if (c >= 'A' && c <= 'Z')
	// 	return (1);
	if (c == '_')
		return (1);
	else if (ft_isalpha(c))
		return (1);
	else if (ft_isdigit(c))
		return (1);
	else if (c == '\\')
		return (1);
	return (0);
}