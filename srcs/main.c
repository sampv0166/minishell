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

    while(arr && arr[i])
    {
        free_me(&arr[i]);
        i++;
    }
    if (arr)
        free_me(arr);
    arr  = NULL;    
}

void free_env()
{
    free_2d_array(env.env_var);
    if (env.pwd)
        free_me (&env.pwd);        
}

int free_everything()
{
    int i;

    i = 0;
    free_env();
    printf("exiting");
    while(i < env.count)
    {
        print_2d_array(env.pa_tkns[i].cmd);
        free_2d_array(env.pa_tkns[i].cmd);
        free_2d_array(env.pa_tkns[i].cmd_splitted);
        free_me(&env.pa_tkns[i].cmd_full);
        free((void *) &env.pa_tkns[i]);
        i++;
    }
    printf("\n%p\n",env.pa_info->arr);
    printf("\n%p\n",env.pa_info->arr1);
    free_2d_array(env.pa_info->arr1);
    free_2d_array(env.pa_info->arr);
    free((void *) &env.pa_info[0]);
    // free_me(&env.pa_info->str);
    //free((void *) env.pa_info);

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
            return (0);
        if(ft_strlen(input) > 0)
            add_history(input);
        else
            continue;            
        ret = input_to_tokens(input);
        if(ret == EXIT_FAILURE)
            free_everything();
       // free (input);
    }
    return (EXIT_FAILURE);
}

int main(int ac, char **argv, char **envp)
{ 
    if (ac && argv[0])
    {
      ac = 0;
      argv = NULL;  
    }
    handle_signals();
    init_env_vars(envp);
    if(env.stat_code)
        free_everything(); 
    if(!get_input())
        free_everything();

    return (EXIT_SUCCESS);    
}