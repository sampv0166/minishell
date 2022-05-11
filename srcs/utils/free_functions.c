#include "../../includes/mini_shell.h"

extern t_env_var env;

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

void free_split_info(t_split *split_info, t_split *split_infoo, char **tokens)
{
    ft_free_str_array(&split_info->arr);
    ft_free_str_array(&tokens);
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
    while(arr[i] != NULL)
    {
        free(arr[i]);
		arr[i] = NULL;
        i++;
    }
	free(arr); 
}

int free_env()
{
    ft_free_str_array(&env.env_var);
    // if (env.pwd)
    //     free_me (&env.pwd); 
    return (0);         
}

int free_everything(t_pars_tokens *tokens)
{
    int i;

    i = 0;
    while(i < env.count)
    {
		free_2d_array(tokens[i].cmd);
        ft_free_str_array(&tokens[i].cmd_cpy);
		ft_free_str_array(&tokens[i].cmd_splitted);
        // free_2d_array(env.pa_tkns[i].cmd_cpy);
        // free_2d_array(env.pa_tkns[i].cmd_splitted);
        free_me(&tokens[i].cmd_full);
		// printf("%d\n", i);
        i++;
    }
    // if (env.count == 1)
	// 	free_2d_array(tokens[i].cmd);
    // {
    //     ft_free_str_array(&tokens[i].cmd_cpy);
    //    ft_free_str_array(&tokens[i].cmd_splitted);
    //     free_me(&tokens[i].cmd_full);
    //     i++;
    // }
    //free(tokens);
    free(tokens);
    // free(tokens);
    return (0);
}
