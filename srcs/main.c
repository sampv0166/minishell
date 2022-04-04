#include "../includes/mini_shell.h"

t_env_var env;

void free_me (char **ptr)
{
    free(*ptr);
    *ptr = NULL;
}

void free_2d_array(char **arr)
{
    int i;
    i = 0;
    print_2d_array(arr);
    while(arr && arr[i])
    {
        free_me(&arr[i]);
        i++;
    }
   free_me(arr); 
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

void free_env()
{
    ft_free_str_array(&env.env_var);
    if (env.pwd)
        free_me (&env.pwd);        
}
int free_everything()
{
    int i;

    i = 0;
    printf("\nexiting %d\n", env.count);

    while(i < env.count)
    {
        ft_free_str_array(&env.pa_tkns[i].cmd);
        ft_free_str_array(&env.pa_tkns[i].cmd_splitted);
        free_me(&env.pa_tkns[i].cmd_full);
        free((void *) &env.pa_tkns[i]);
        i++;
    }
   // free_2d_array(env.split);
    // i = 8;
    // print_2d_array(env.split);
    // while(env.split && env.split[i])
    // {
    //     free_me(&env.split[i]);
    //     i++;
    // }
    //free_env();
    // free_me(&env.pa_info->str);
    free((void *) env.pa_info);
    return (0);
}

static int get_input()
{
    char *input;
    int ret;
    
    input = NULL;
    ret = 0;

    while(1)
    {
        input = readline("MS SHELL====>");
        if(input == NULL)
        {
            return (0);
        }
        if(ft_strlen(input) > 0)
            add_history(input);
        else
            continue;            
        ret = input_to_tokens(input);
        if(!ret)
        {
            free_everything();
        }
    }
    return (EXIT_FAILURE);
}

int main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
    handle_signals();
    init_env_vars(envp);
    if(env.stat_code)
        free_everything(); 
    if(!get_input())
    {
        free_env();
        //free_everything();
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);    
}