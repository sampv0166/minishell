#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	ft_isqt(char c)
{
	if (c == 34 || c == 39)
		return (c);
	return (0);
}

int	parse_cmd(char *str)
{
	int	i;
	int	trig;
	int	qte;

	i = 0;
	trig = 0;
	qte = 0;
	while (str[i])
	{
		if (ft_isqt(str[i]))
		{
			qte = str[i];
			i++;
			while (str[i] && str[i] != qte)
				i++;
			if (str[i] && str[i] == qte)
			{
				qte = 0;
				i++;
			}
			else
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	check_cmds_qtes(char **str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] != NULL)
	{
		ret = parse_cmd(str[i]);
		if (ret)
			break;
		i++;
	}
	return (ret);
}

int main(void)
{
	char	**str;

	str = (char **)malloc(sizeof(char *) * 5);
	str[0] = strdup("file\"\'");
	str[1] = NULL;
	printf("%d\n", check_cmds_qtes(str));
	return (0);
}
