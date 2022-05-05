#include "../../includes/mini_shell.h"

char	*ft_strtolower(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = strdup(str);
	while (tmp[i])
	{
		str[i] = ft_tolower(tmp[i]);
		i++;
	}
	str[i] = '\0';
	free(tmp);
	return (str);
}
