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

char	*tilde_dir(void)
{
	int		count;
	char	s[1000];
	int		i;
	char	*tmp;

	tmp = malloc(5);
	count = 0;
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
		if (count > 2)
		{
			if (chdir(".."))
				break;
		}
		else if (!strcmp(tmp, "/home"))
		{
			if (chdir("student42abudhabi"))
				break;
		}
		else if (!strcmp(tmp, "/"))
		{
			if (chdir("home"))
				break;
		}
	}
	if (count != 2)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

char	*slash_dir(void)
{
	int		count;
	char	s[1000];
	int		i;
	char	*tmp;

	tmp = calloc(1, 5);
	count = 0;
	while (count != 1 || (strlen(tmp) != 1))
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
		if (count > 1)
		{
			if (chdir(".."))
				break;
		}
		else if (!strcmp(tmp, "/home"))
		{
			if (chdir(".."))
				break;
		}
	}
	if (count != 1 || (strcmp(tmp, "/") && strcmp(tmp, "//")))
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

int	chge_dir(char *path, char *pwd)
{
	int		i;
	int		count;
	char	*tmp;
	char	s[1000];
	char	*old_pwd;

	i = 0;
	count = 0;
	tmp = malloc(5);
	if (pwd != NULL)
		pwd = strdup(getcwd(s, 1000));
	if (!strcmp(path, "~"))
	{
		free(tmp);
		tmp = tilde_dir();
		if (tmp != NULL)
		{
			old_pwd = strdup(pwd);
			free(pwd);
			pwd = strdup(getcwd(s, 1000));
		}
	}
	else if (!strcmp(path, "//"))
	{
		free(tmp);
		tmp = slash_dir();
		if (tmp != NULL)
		{
			old_pwd = strdup(pwd);
			free(pwd);
			pwd = strdup("//");
		}
	}
	else if (!strcmp(path, "/"))
	{
		free(tmp);
		tmp = slash_dir();
		if (tmp != NULL)
		{
			old_pwd = strdup(pwd);
			free(pwd);
			pwd = strdup(getcwd(s, 1000));
		}
	}
	free(tmp);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	cd(char **str)
{
	int	i;
	char	*pwd;
	char	*old_pwd;
	char	s[1000];

	i = 0;
	pwd = strdup(getcwd(s, 1000));
	while (str[i] != NULL)
	{
		if (!strcmp(str[i], "//") || !strcmp(str[i], "/"))
		{
			if (!chdir("/"))
			{
				if (!strcmp(str[i], "//"))
					chge_dir("//", pwd);
				else if (!strcmp(str[i], "/"))
					chge_dir("/", pwd);
			}
			return (0);
		}
		else if (!chdir(str[i]))
		{
			chdir("..");
			return (chge_dir(str[i], NULL));
		}
		else if (str[i][0] == '~')
			chge_dir("~", NULL);
		else
		{
			printf("cd: %s: Not a directory\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}