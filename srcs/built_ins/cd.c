#include "../../includes/mini_shell.h"

extern t_env_var env;
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

/*
cd brings the directory to the tilde
cd should work with only two arguments, example: cd Desktop without quotes. It should return an error with more than two args.
cd / brings the directory to /
cd ~ brings the directory to the tilde
if changing directory is successful. PWD takes the value of the current path of the directory and OLDPWD takes the old path of the current directory.
RETURN 0 for the success and 1 for an ERROR.
cd should also work with env variables as an argument. For example cd $OLDPWD
*/

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
	if (pwd == NULL)
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
	else
	{
		old_pwd = strdup(pwd);
		free(pwd);
		pwd = strdup(getcwd(s, 1000));
	}
	free(tmp);
	free(pwd);
	free(old_pwd);
	return (0);
}

int	chge_tld_mis(char *str, char *pwd)
{
	char	*tmp;
	char	*old_pwd;
	int		count;
	char	s[1000];

	count = 0;
	if (*str == '~')
	{
		tmp = tilde_dir();
		str = strchr(str, '/');
		if (*str)
			++str;
		if (!chdir(str))
		{
			old_pwd = strdup(pwd);
			free(pwd);
			pwd = strdup(getcwd(s, 1000));
			free(tmp);
			free(old_pwd);
			free(pwd);
			return (0);
		}
		free(tmp);
		chdir(pwd);
		free(pwd);
		printf("cd: ~/%s: Not a directory\n", str);
	}
	return (1);
}

int	cd(char **str)
{
	int	i;
	char	*pwd;
	char	*tmp;
	char	s[1000];
	int		j;
	int		k;
	int		qte;
	char	*fetched;

	i = 1;
	qte = 0;
	j = 0;
	k = 0;
	printf("OLD: %s\n", getcwd(s, 1000));
	pwd = strdup(getcwd(s, 1000));
	if (str[i] != NULL)
	{
		if (str[i][0] == 34 || str[i][0] == 39)
			qte = str[i][0];
		tmp = strdup(str[i]);
		i = 0;
		j = 0;
		while (tmp[j])
		{
			if (tmp[j] != qte)
			{
				str[i][k] = tmp[j];
				k++;
			}
			j++;
		}
		str[i][k] = '\0';
		free(tmp);
	}
	i = 1;
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
			return (chge_dir(str[i], pwd));
		}
		else if (str[i][0] == '~')
		{
			if (strlen(str[i]) <= 2)
			{
				free(pwd);
				chge_dir("~", NULL);
			}
			else
				chge_tld_mis(str[i], pwd);
		}
		else if (str[i][0] == '$')
		{
			if (ft_isalpha(str[i][1]) || ft_isdigit(str[i][1]))
			{
				++str[i];
				// fetched = ft_strdup(fetch_echo(str[i], env.env_var));
				// if (*fetched)
				ft_putendl_fd(str[i], 1);
				// if (*fetched && !chdir(fetched))
				// {
				// 	chng_dir(pwd);
				// 	return (0);
				// }
				// free(pwd);
				// chge_dir("~", NULL);
			}
			else
			{
				if (str[i][1] == '?' && (ft_strlen(str[i]) == 2))
					printf("cd: %d: Not a directory\n", env.stat_code);
				else
					printf("cd: %s: Not a directory\n", str[i]);
				return (1);
			}
		}
		else
		{
			free(pwd);
			printf("cd: %s: Not a directory\n", str[i]);
			return (1);
		}
		i++;
	}
	if (i == 1)
	{
		free(pwd);
		chge_dir("~", NULL);
	}
	printf("NEW: %s\n", getcwd(s, 1000));
	return (0);
}
// int main(void)
// {
// 	char	**str;
// 	char	s[1000];

// 	str = (char **)malloc(sizeof(char *) * 5);
// 	str[0] = strdup("$?");
// 	str[1] = NULL;
// 	printf("%s\n", getcwd(s, 1000));
// 	cd(str);
// 	printf("%s\n", getcwd(s, 1000));
// 	free(str[0]);
// 	free(str);
// 	return (0);
// }