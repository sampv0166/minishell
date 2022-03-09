#include "../includes/mini_shell.h"

static int get_input(t_env_var *env)
{
    char *input;
    int ret;
    
    while(1)
    {
        input = readline("MS SHELL====>");
        if(ft_strlen(input) > 0)
            add_history(input);
        if(input == NULL)
            exit(EXIT_SUCCESS); // TODO : free everything  
        ret = input_to_tokens(input, env);
        if(ret == EXIT_FAILURE)
            return (EXIT_FAILURE); // TODO : free everything  
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
        return (EXIT_FAILURE); // TODO :  free everything
    if(!get_input(env))
        return (EXIT_FAILURE); // TODO :  free everything
    return (EXIT_SUCCESS);    
}