// #include "../../includes/mini_shell.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// extern t_env_var env;

/*
cd brings the directory to the tilde
cd should work with only two arguments, example: cd Desktop without quotes. It should return an error with more than two args.
cd / brings the directory to /
cd ~ brings the directory to the tilde
if changing directory is successful. PWD takes the value of the current path of the directory and OLDPWD takes the old path of the current directory.
RETURN 0 for the success and 1 for an ERROR.
*/

typedef struct	s_info
{
	int	tilde;
	int	slash;
}				t_info;

int	chge_dir(char *path)
{
	int	i;
	int	count;
	char	*tmp;
	char	s[1000];

	i = 0;
	count = 0;
	tmp = malloc(sizeof(char) * 5);
	if (!strcmp(path, "~"))
	{
		while (count != 2)
		{
			count = 0;
			i = 0;
			free(tmp);
			tmp = strdup(getcwd(s, 1000));
			while (tmp[i])
			{
				if (tmp[i] == '/')
					count++;
				i++;
			}
			printf("Count: %d\tDir: %s\n", count, tmp);
			if (count != 2)
				chdir("..");
		}
	}
	free(tmp);
}

int	cd(char **str)
{
	int	i;
	char	s[1000];
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	// while (str[i] != NULL)
	// {
	// 	if (str[i][0] == '~' && str[i][1] == '/')
	// 	{
	// 		chge_dir("~");
	// 	}
	// 	i++;
	// }
	return (0);
}

// int main(void)
// {
// 	char	**str;

// 	str = (char **)malloc(sizeof(char *) * 5);
// 	str[0] = strdup("~/Desktop/built-ins");
// 	str[1] = NULL;
// 	cd(str);
// 	free(str[0]);
// 	free(str);
// 	return (0);
// }