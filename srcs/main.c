#include "../includes/mini_shell.h"

t_env_var env;

static int get_input()
{
    char *input;
    
    input = NULL;
    while(1)
    {
        ft_putstr_fd("\n", 2);
        ft_putstr_fd("exit code :   ", 2);
        ft_putnbr_fd(env.stat_code, 2);
        ft_putstr_fd("\n", 2);
        input = readline("MS SHELL====>");
        if(input == NULL)
        {
            free_env();
            return (0);
        }
        if(ft_strlen(input) > 0)
            add_history(input);
        else
            continue;            
        input_to_tokens(input);
        if(!env.stat_code)
           ;//free_everything();
    }
    return (0);
}

int main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
    handle_signals();
    if(init_env_vars(envp))
        free_env();
    return(get_input());   
}