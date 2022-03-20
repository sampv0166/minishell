#include "../includes/mini_shell.h"

void free_me (char **ptr)
{
    free(*ptr);
    *ptr = NULL;
}

void free_everything(int exit_status)
{

}

static int get_input(t_env_var *env)
{
    char *input;
    int ret;
    
    input = NULL;
    ret = 0;

    while(1)
    {
        input = readline("MS SHELL====>");
        if(ft_strlen(input) > 0)
            add_history(input);
        if(input == NULL)
            exit(EXIT_SUCCESS); 
        ret = input_to_tokens(input, env);
        if(ret == EXIT_FAILURE)
            return (EXIT_FAILURE);
        free (input);
    }
    return (EXIT_FAILURE);
}

int main(int ac, char **argv, char **envp)
{
    t_env_var *env;
    handle_signals();
    env = init_env_vars(envp);
    int i;
    i = 0;
    if(env == NULL)
        return (EXIT_FAILURE); 
    if(!get_input(env))
        return (EXIT_FAILURE); 
    return (EXIT_SUCCESS);    
}