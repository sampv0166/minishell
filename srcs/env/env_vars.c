/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:14 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 16:19:16 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"
/*
  gets the length of the original env variable
*/

int	get_env_arr_len(char **arr)
{
	int	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}
/*
This function saves a copy of the env variable .
*/

char	**save_env(char **env_var)
{
	char	**env_v;
	int		i;
	int		arr_len;

	i = 0;
	arr_len = 0;
	env_v = NULL;
	arr_len = get_env_arr_len(env_var);
	env_v = malloc (sizeof (char *) * (arr_len + 1));
	if (env_v == NULL)
		return (NULL);
	while (env_var[i])
	{
		env_v[i] = ft_strdup(env_var[i]);
		i++;
	}
	env_v[i] = NULL;
	return (env_v);
}
/*
*/
/*
  This function compares each string in the env variable 
  with the value that we want to get.
  checks if the unmatching charatcer is -61.
  -61 means the it comapred a null character and equal sign.
  find the index of the character '=' with ft_strchr function.
  if the length is greater than 0, return a null.
  otherwise retrun duplicate value.
  !expected input 
  ? char **
  TERM_PROGRAM_VERSION=1.65.2
  GNOME_DESKTOP_SESSION_ID=this-is-deprecated
  APPLICATION_INSIGHTS_NO_DIAGNOSTIC_CHANNEL=true
  GNOME_SHELL_SESSION_MODE=ubuntu
  SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
  XMODIFIERS=@im=ibus
  DESKTOP_SESSION=ubuntu
  BAMF_DESKTOP_FILE_HINT=/var/lib/snapd/desktop/applications/code_code
  .desktop
  NO_AT_BRIDGE=1
  GTK_MODULES=gail:atk-bridge
  PWD=/home/abdu/Desktop/minishell
  ? "PWD"

  !expected output
  /home/abdu/Desktop/minishell
*/

char	*get_env_value(char *var)
{
	int		i;
	char	*val;

	i = 0;
	val = NULL;
	while (g_env.env_var[i] != NULL)
	{
		if (ft_strcmp(var, g_env.env_var[i]) == -61)
		{
			val = ft_strchr(g_env.env_var[i++], '=') + 1;
			if (ft_strlen(val) == 0)
				val = ft_calloc(1, sizeof (char));
			else
				val = ft_strdup(val);
			break ;
		}
		i++;
	}
	return (val);
}

/*
  This function is used to intialize and save env variables
*/
int	init_env_vars(char **envp)
{
	g_env.env_var = save_env(envp);
	if (g_env.env_var != NULL)
	{
		g_env.trigger = 0;
		g_env.s_pid = 0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
