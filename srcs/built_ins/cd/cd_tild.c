/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:31:19 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:31:20 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/*This function is to change the directory to the home directory of the system*/
void	ch_home(void)
{
	int		i;
	int		count;
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

void	chge_dir_tild(int count)
{
	char	*tmp;
	char	s[1000];

	tmp = NULL;
	tmp = ft_strdup(getcwd(s, 1000));
	if (count == 1 && ft_strlen(tmp) == 1)
	{
		free(tmp);
		tmp = get_env_dollar("$LOGNAME");
		chdir("Users");
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

/*This function changes the directory to the ~ location*/
void	ch_tild(void)
{
	int		count;
	char	s[1000];
	char	*tmp;
	int		i;

	count = 0;
	i = 0;
	ch_home();
	tmp = ft_strdup(getcwd(s, 1000));
	while (tmp[i])
	{
		if (tmp[i] == '/')
			count++;
		i++;
	}
	free(tmp);
	if (count < 2)
		chge_dir_tild(count);
}

/*If the command is passed from user is ~. This function changes
the directory and updates the values for pwd and old pwd in env*/
int	chge_tilde(char *pwd)
{
	char	s[1000];
	char	*new;

	ch_tild();
	new = ft_strdup(getcwd(s, 1000));
	chge_pwd(new);
	chge_old_pwd(pwd);
	free(new);
	free(pwd);
	return (0);
}

/*If the chdir is successful, then it updates 
the values of pwd and old_pwd in env*/
int	chge_c_dir(char *pwd)
{
	char	*new;
	char	s[1000];

	new = ft_strdup(getcwd(s, 1000));
	chge_pwd(new);
	chge_old_pwd(pwd);
	free(new);
	free(pwd);
	return (0);
}
