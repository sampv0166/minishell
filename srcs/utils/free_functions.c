#include "../../includes/mini_shell.h"

extern t_env_var env;

void free_split_info(t_split *split_info, t_split *split_infoo, char **tokens)
{
    ft_free_str_array(&split_info->arr);
    ft_free_str_array(&tokens);
    free( (void *) split_info);
    free( (void *) split_infoo);
}

void free_me (char **ptr)
{
    free(*ptr);
    *ptr = NULL;
}

void free_2d_array(char **arr)
{
    int i;
    i = 0;
    while(arr && arr[i])
    {
        free(arr[i]);
        i++;
    }
   free(arr); 
}


void	ft_free_str_array(char ***arr)
{
	int	i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		free_me(&(*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

int free_env()
{
    ft_free_str_array(&env.env_var);
    if (env.pwd)
        free_me (&env.pwd); 
    return (0);         
}

int free_everything()
{
    int i;
    i = 0;
    while(env.count != 1 && i < env.count)
    {
        ft_free_str_array(&env.pa_tkns[i].cmd);
        ft_free_str_array(&env.pa_tkns[i].cmd_splitted);
        free_me(&env.pa_tkns[i].cmd_full);
        i++;
    }
    free(env.pa_tkns);
    return (0);
}
