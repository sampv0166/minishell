#include "../../includes/mini_shell.h"

static int	check_qte_str(char *str)
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

// static void	cpy_str(char *str, int qte)
// {
// 	char	*tmp;
// 	int		j;
// 	int		k;

// 	j = 0;
// 	tmp = ft_strdup(str);
// 	k = 0;
// 	while (tmp[k])
// 	{
// 		if (tmp[k] != qte)
// 		{
// 			str[j] = tmp[k];
// 			j++;
// 		}
// 		k++;
// 	}
// 	str[j] = '\0';
// 	free(tmp);
// }

void	delimit_qtes(char *str)
{
	int		qte;
	int		j;
	int		k;
	int		trig;
	char	*tmp;

	trig = 0;
	tmp = NULL;
	qte = check_qte_str(str);
	k = 0;
	j = 0;
	if (str != NULL)
	{
		if (qte)
		{
			qte = 0;
			tmp = strdup(str);
			while (str[k])
			{
				if (ft_isqt(str[k]))
				{
					if (ft_isqt(str[k]) == qte)
					{
						if (!trig)
						{
							trig = 1;
							qte = str[k];
						}
						else
						{
							trig = 0;
							qte = 0;
						}
						k++;
					}
					else if (!qte)
					{
						qte = ft_isqt(str[k]);
						trig = 1;
						k++;
					}
					else
					{
						tmp[j] = str[k];
						j++;
						k++;
					}
				}
				else
				{
					tmp[j] = str[k];
					j++;
					k++;
				}
			}
			tmp[j] = '\0';
			j = 0;
			while (tmp[j])
			{
				str[j] = tmp[j];
				j++;
			}
			str[j] = '\0';
			free(tmp);
		}
	}
}
