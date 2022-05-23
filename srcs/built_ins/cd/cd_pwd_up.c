/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:31:22 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:31:23 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/*Updating values for new PWD in env*/
void	chge_pwd(char *pwd)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	i = get_env("PWD");
	if (g_env.env_var[i] == NULL)
	{
		new = ft_strdup("PWD=");
		new = ft_strjoin(new, pwd);
		g_env.env_var = new_env(new);
		free(new);
	}
	else
	{
		free(g_env.env_var[i]);
		g_env.env_var[i] = ft_strdup("PWD=");
		g_env.env_var[i] = ft_strjoin(g_env.env_var[i], pwd);
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
	if (g_env.env_var[i] == NULL)
	{
		new = ft_strdup("OLDPWD=");
		new = ft_strjoin(new, old_pwd);
		g_env.env_var = new_env(new);
		free(new);
	}
	else
	{
		free(g_env.env_var[i]);
		g_env.env_var[i] = ft_strdup("OLDPWD=");
		g_env.env_var[i] = ft_strjoin(g_env.env_var[i], old_pwd);
	}	
}
