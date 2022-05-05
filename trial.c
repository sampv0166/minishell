#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int	ft_isenv(char c)
{
	// if (c >= 'A' && c <= 'Z')
	// 	return (1);
	if (c == '_')
		return (1);
	else if (isalpha(c))
		return (1);
	else if (isdigit(c))
		return (1);
	else if (c == '\\')
		return (1);
	return (0);
}

int main(void)
{
	int	qte;
	char	*tmp;
	int		k;

	qte = 0;
	k = 0;
	tmp = strdup("$?$?$?$?$?$?$");
	while (tmp[k])
	{
		if (qte != 39 && (tmp[k] == '$' && (tmp[k + 1] == '?' || ft_isenv(tmp[k + 1]))))
		{
			k +=2;
			printf("success\n");
			printf("%s\n", &tmp[k]);
		}
		k++;
	}

}