#include "../../../includes/mini_shell.h"

extern t_env_var	env;

/*
cd brings the directory to the tilde
cd should work with only two arguments, example: cd Desktop without quotes. It should return an error with more than two args.
cd / brings the directory to /
cd ~ brings the directory to the tilde
if changing directory is successful. PWD takes the value of the current path of the directory and OLDPWD takes the old path of the current directory.
RETURN 0 for the success and 1 for an ERROR.
cd should also work with env variables as an argument. For example cd $OLDPWD
*/

/*If the command is passed from user is // or /. This function changes
the directory and updates the values for pwd and old pwd in env*/
static int	chge_dir(char *pwd, char *str)
{
	int		i;
	char	s[1000];
	char	*new;

	ch_home();
	chge_pwd(str);
	chge_old_pwd(pwd);
	free(pwd);
	return (0);
}

char	*get_pwd(void)
{
	int		i;
	char	*pwd;
	char	s[1000];

	i = 0;
	i = get_env("PWD");
	if (env.env_var[i] == NULL)
		pwd = ft_strdup(getcwd(s, 1000));
	else
		pwd = get_env_dollar("$PWD");
	return (pwd);
}

int	cd(char **str)
{
	int		i;
	char	*pwd;
	char	s[1000];

	i = 0;
	/*Delimiting quotes*/
	delimit_qtes(str[1]);
	/*Getting current PWD if the PWD doesn't exist in env then get the current one using getcwd*/
	i = 1;
	pwd = get_pwd();
	if (str[i] == NULL)
		return (chge_tilde(pwd));
	else if (!ft_strcmp(str[i], "//"))
		return (chge_dir(pwd, "//"));
	else if (!ft_strcmp(str[i], "/"))
		return (chge_dir(pwd, "/"));
	else if (!chdir(str[i]))
		return (chge_c_dir(pwd));
	else
	{
		/*Error Message*/
		free(pwd);
		printf("cd: %s: No such file or directory\n", str[i]);
		return (1);
	}
	return (0);
}
