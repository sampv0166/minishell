#include "../../../includes/mini_shell.h"

extern t_env_var	env;

/*Updating values for new PWD in env*/
void	chge_pwd(char *pwd)
{
	int		i;
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
void	chge_old_pwd(char *old_pwd)
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
