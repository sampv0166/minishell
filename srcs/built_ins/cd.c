#include "../../includes/mini_shell.h"

extern t_env_var env;

/*
cd brings the directory to the tilde
cd should work with only two arguments, example: cd Desktop without quotes. It should return an error with more than two args.
cd / brings the directory to /
cd ~ brings the directory to the tilde
if changing directory is successful. PWD takes the value of the current path of the directory and OLDPWD takes the old path of the current directory.
RETURN 0 for the success and 1 for an ERROR.
cd should also work with env variables as an argument. For example cd $OLDPWD
*/

/*Updating values for new PWD in env*/
static void	chge_pwd(char *pwd)
{
	int	i;
	char	*new;

	i = 0;
	new = NULL;
	i = get_env("PWD");
	if (env.env_var[i] == NULL)
	{
		new = ft_strdup("PWD=");
		new = ft_strjoin(new, pwd);
		env.env_var = new_env(new);
		free(new);
	}
	else
	{
		free(env.env_var[i]);
		env.env_var[i] = ft_strdup("PWD=");
		env.env_var[i] = ft_strjoin(env.env_var[i], pwd);
	}
}

/*Updating values for old PWD in env*/
static void	chge_old_pwd(char *old_pwd)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	i = get_env("OLDPWD");
	if (env.env_var[i] == NULL)
	{
		new = ft_strdup("OLDPWD=");
		new = ft_strjoin(new, old_pwd);
		env.env_var = new_env(new);
		free(new);
	}
	else
	{
		free(env.env_var[i]);
		env.env_var[i] = ft_strdup("OLDPWD=");
		env.env_var[i] = ft_strjoin(env.env_var[i], old_pwd);
	}	
}

/*This function is to change the directory to the home directory of the system*/
static void ch_home(void)
{
	int	i;
	int	count;
	char	*tmp;
	char	s[1000];

	i = 0;
	count = 0;
	tmp = ft_strdup(getcwd(s, 1000));
	while (count > 1 || ft_strlen(tmp) != 1)
	{
		i = 0;
		count = 0;
		chdir("..");
		free(tmp);
		tmp = ft_strdup(getcwd(s, 1000));
		while (tmp[i])
		{
			if (tmp[i] == '/')
				count++;
			i++;
		}
	}
	free(tmp);
}

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

/*This function changes the directory to the ~ location*/
static void	ch_tild(void)
{
	int	count;
	char	s[1000];
	char	*tmp;
	int		i;

	count = 0;
	i = 0;
	tmp = ft_strdup(getcwd(s, 1000));
	while(tmp[i])
	{
		if (tmp[i] == '/')
			count++;
		i++;
	}
	free(tmp);
	if (count > 2)
	{
		while (count > 2)
		{
			chdir("..");
			tmp = ft_strdup(getcwd(s, 1000));
			count = 0;
			i = 0;
			while(tmp[i])
			{
				if (tmp[i] == '/')
					count++;
				i++;
			}
			free(tmp);
		}
	}
	else if (count < 2)
	{
		tmp = ft_strdup(getcwd(s, 1000));
		if (count == 1 && ft_strlen(tmp) == 1)
		{
			free(tmp);
			tmp = get_env_dollar("$LOGNAME");
			chdir("home");
			chdir(tmp);
			free(tmp);
		}
		else if (count == 1 && ft_strlen(tmp) > 1)
		{
			free(tmp);
			tmp = get_env_dollar("$LOGNAME");
			chdir(tmp);
			free(tmp);
		}
	}
}

/*If the command is passed from user is ~. This function changes
the directory and updates the values for pwd and old pwd in env*/
static int	chge_tilde(char *pwd)
{
	char	s[1000];
	char	*new;
	int		i;

	i = 0;
	ch_tild();
	new = ft_strdup(getcwd(s, 1000));
	chge_pwd(new);
	chge_old_pwd(pwd);
	free(new);
	free(pwd);
	return (0);
}

/*If the chdir is successful, then it updates the values of pwd and old_pwd in env*/
static int	chge_c_dir(char *pwd)
{
	char	*new;
	char	s[1000];
	int		i;

	i = 0;
	new = ft_strdup(getcwd(s, 1000));
	chge_pwd(new);
	chge_old_pwd(pwd);
	free(new);
	free(pwd);
	return (0);
}

/*
This function is for changing the directory with respect to ~
Example: ~/Desktop/trial/
*/
static int	tild_c_dir(char *pwd, char *str)
{
	int	i;
	char	*tmp;
	char	*new;
	char	s[1000];
	int		len;

	i = 0;
	len = 0;
	new = NULL;
	/*Changing to tilde*/
	ch_tild();
	len = ft_strlen(str);
	tmp = ft_calloc(1, len + 1);
	/*Now we are getting the value after the tilde*/
	while (str[i]  != '/')
		i++;
	++i;
	len = 0;
	while (str[i])
	{
		tmp[len] = str[i];
		len++;
		i++;
	}
	tmp[len] = '\0';
	/*Now we are changing the directory after the tilde. Also,
	we are checking if the return value of chdir is zero or not*/
	if (!chdir(tmp))
	{
		/*Since the return value of chdir is zero this means that
		we can change the PWD and OLDPWD value in env*/
		free(tmp);
		tmp = ft_strdup(getcwd(s, 1000));
		chge_pwd(tmp);
		free(tmp);
	}
	else
	{
		/*Here it failed changing the directory so we can go
		back from where we started and return 1*/
		chdir("..");
		chdir("..");
		chdir(pwd);
		free(tmp);
		tmp = ft_strdup(getcwd(s, 1000));
		free(pwd);
		free(tmp);
		return(1);
	}
	chge_old_pwd(pwd);
	free(pwd);
	return(0);
}

/*This function is to manipulate the dollar string to fetch the value of the env
variable and changes the directory according to it*/
int	dol_dir(char *pwd, char *str)
{
	int		i;
	char	*tmp;
	char	*cur;
	char	s[1000];

	i = 0;
	cur = ft_strdup(pwd);
	tmp = NULL;
	if (ft_strstr(str, "$") && (ft_strlen(str) > 1))
	{
		free(cur);
		cur = ft_strdup(&str[1]);
		while (ft_isenv(cur[i]) && cur[i])
			i++;
		cur[i] = '\0';
		i = get_env(cur);
		if (env.env_var[i] != NULL)
		{
			tmp = ft_calloc(ft_strlen(cur) + 2, sizeof(char));
			tmp[0] = '$';
			tmp = ft_strjoin(tmp, cur);
			free(cur);
			cur = ft_strdup(tmp);
			free(tmp);
			tmp = get_env_dollar(cur);
			free(cur);
			cur = ft_strdup(tmp);
			if (ft_strchr(str, '/'))
				cur = ft_strjoin(cur, ft_strchr(str, '/'));
			free(tmp);
		}
	}
	else
		i = get_env(&str[1]);
	if (env.env_var[i] == NULL)
	{
		/*If env variable does not exist it changes the directory to tilde and
		updates it*/
		ch_tild();
		free(cur);
		cur = ft_strdup(getcwd(s, 1000));
		chge_pwd(cur);
		chge_old_pwd(pwd);
	}
	else if (!chdir(cur))
	{
		if (!ft_strcmp(cur, "//"))
		{
			free(cur);
			cur = ft_strdup(("//"));
		}
		else
		{
			free(cur);
			cur = ft_strdup(getcwd(s, 1000));
		}
		chge_pwd(cur);
		chge_old_pwd(pwd);
	}
	else if (ft_strstr(cur, "/home"))
	{
		/*This condition is for changing the dir to $OLDPWD
		and if in some we encounter any error it goes back from where it started*/
		ch_home();
		if (!chdir(cur))
		{
			free(cur);
			cur = ft_strdup(getcwd(s, 1000));
			chge_pwd(cur);
			chge_old_pwd(pwd);
		}
		else
		{
			free(cur);
			chdir(pwd);
			free(pwd);
			return (1);
		}
	}
	else
	{
		/*Error Message*/
		free(pwd);
		printf("cd: %s: No such file or directory\n", cur);
		free(cur);
		return (1);
	}
	free(cur);
	free(pwd);
	return (0);
}

int	cd(char **str)
{
	int	i;
	char	*pwd;
	char	s[1000];

	i = 0;
	i = get_env("PWD");
	if (env.env_var[i] == NULL)
		pwd = ft_strdup(getcwd(s, 1000));
	else
		pwd = get_env_dollar("$PWD");
	i = 1;
	if (str[i] == NULL)
		return(chge_tilde(pwd));
	else if (!ft_strcmp(str[i], "//"))
		return (chge_dir(pwd, "//"));
	else if (!ft_strcmp(str[i], "/"))
		return (chge_dir(pwd, "/"));
	else if (!ft_strcmp(str[i], "~") || !ft_strcmp(str[i], "~/"))
		return (chge_tilde(pwd));
	else if (!chdir(str[i]))
		return(chge_c_dir(pwd));
	else if (str[i][0] == '~')
		return (tild_c_dir(pwd, str[i]));
	else if (str[i][0] == '$')
		return (dol_dir(pwd, str[i]));
	else
	{
		/*Error Message*/
		free(pwd);
		printf("cd: %s: No such file or directory\n", str[i]);
		return (1); 
	}
}