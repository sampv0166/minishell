/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhtar & apila-va <makhtar@student.42a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:30:16 by makhtar & a       #+#    #+#             */
/*   Updated: 2022/05/23 13:30:17 by makhtar & a      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/*Returning the index of the env varibale in fetching*/

/*In this while loop I check for the 
first occurence of the string which I'm looking for in env varibale*/

/*The moment it encounters any string I pass the value of 
index of env and check the variable if that variable 
matches with my str.In case if it doesn't match the loop 
is still on running until it matches the requirements or 
it reaches to the of NULL in env*/

int	get_env(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(g_env.env_var[i]);
	while (g_env.env_var[i] != NULL)
	{
		if (ft_strstr(g_env.env_var[i], str))
		{	
			j = 0;
			free(tmp);
			tmp = ft_strdup(g_env.env_var[i]);
			while (tmp[j] != '=' && tmp[j] != '\0')
				j++;
			tmp[j] = '\0';
			if (!ft_strcmp(tmp, str))
				break ;
		}
		i++;
	}
	free(tmp);
	return (i);
}
