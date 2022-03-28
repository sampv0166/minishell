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

    while(arr[i])
    {
        free_me(&arr[i]);
        i++;
    }
    if (arr)
        free_me(arr);
}

void free_env()
{
    int i;

    i = 0;

    free_2d_array(env.env_var);
    if (env.pwd)
        free_me (&env.pwd);        
}

int free_everything()
{
    free_env();
    printf("exiting");
    exit(0);
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
        ret = input_to_tokens(input);
        // if(ret == EXIT_FAILURE)
        //     free_everything();
       // free (input);
    }
    return (EXIT_FAILURE);
}

int main(int ac, char **argv, char **envp)
{ 
    handle_signals();
    init_env_vars(envp);
     
    if(env.stat_code)
        free_everything(); 
    if(!get_input())
        free_everything();
    return (EXIT_SUCCESS);    
}