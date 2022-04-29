#include "../../includes/mini_shell.h"

static int	check_qte_str(char *str)
{
	if (str[0] == 34 || str[0] == 39)
		return (str[0]);
	else if (last_char(str) == 34 || last_char(str) == 39)
		return (last_char(str));
	return (0);
}

static void	cpy_str(char *str, int qte)
{
	char	*tmp;
	int		j;
	int		k;

	j = 0;
	tmp = ft_strdup(str);
	k = 0;
	while (tmp[k])
	{
		if (tmp[k] != qte)
		{
			str[j] = tmp[k];
			j++;
		}
		k++;
	}
	str[j] = '\0';
	free(tmp);
}

void	delimit_qtes(char *str)
{
	int		qte;
	int		j;
	int		k;

	if (str != NULL)
	{
		qte = check_qte_str(str);
		if (qte)
			cpy_str(str, qte);
	}
}
