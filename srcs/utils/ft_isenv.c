#include "../../includes/mini_shell.h"

int	ft_isenv(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}