#include "../../includes/mini_shell.h"

char	**ft_2d_str_cpy(char **str)
{
	char	**cpy;
	int		i;
	int		len;

	len = get_len(str);
	cpy = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (str[i] != NULL)
	{
		cpy[i] = ft_strdup(str[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}