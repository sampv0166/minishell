/*Returning the index of the env varibale in fetching*/
#include "../../includes/mini_shell.h"

extern t_env_var	env;

int	get_env(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(env.env_var[i]);
	while (env.env_var[i] != NULL)
	{
		/*In this while loop I check for the first occurence of the string which I'm looking for in env varibale*/
		if (ft_strstr(env.env_var[i], str))
		{
			/*The moment it encounters any string I pass the value of index of env and check the variable if that variable matches with my str.
			In case if it doesn't match the loop is still on running until it matches the requirements or it reaches to the of NULL in env*/
			j = 0;
			free(tmp);
			tmp = ft_strdup(env.env_var[i]);
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
