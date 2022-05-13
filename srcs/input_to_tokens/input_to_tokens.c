#include "../../includes/mini_shell.h"

extern t_env_var env;

char **join_toks(char **tok1, char **tok2)
{
    int len;
    len = (get_2d_arr_len2(tok1) + get_2d_arr_len2(tok2))  + 1;
    char **new_toks;
    int i;
    int j;
    new_toks = malloc(sizeof(char *) * len + 1);
    i = 0;
    j = 0;
    while(tok1[i])
    {
        new_toks[i] = ft_strdup(tok1[i]);
        i++;
    }
    while(tok2[j])
    {
        new_toks[j + i] = ft_strdup(tok2[j]);
        j++;
    }
    new_toks[j + i] = NULL;
    ft_free_str_array(&tok1);
    ft_free_str_array(&tok2);
    return (new_toks);
}



char *join_pipes()
{
    char *in;
    char *buf;
    char **toks;

    in = NULL;
    buf = NULL;
    while(1)
    {
        if (read_buf(&buf, &in))
            return (NULL);
        in = ft_strjoin(in, buf);
        if(ft_strlen(in) > 0)
        {
            if(in[ft_strlen(in) - 1] == '|')
            {
                if(in && in[0] == '|')
                    break ;
                continue;
            }
            else
                break;  
        }
    }
    return (in);
}

char **get_command_for_pipe(char **toks, char ***tokens, char *input)
{
    toks = split_to_tokens(input);
    *tokens = join_toks(*tokens, toks);
    free_me(&input);
    if (!is_token_syntax_valid(*tokens))
    { 
        ft_free_str_array(tokens);
        ft_free_str_array(&toks);
        free_me(&input);
        return (NULL);
    }
    return (*tokens);
}

char **tokens_split(char *input)
{
    char **tokens;
    char **toks;
    tokens = split_to_tokens(input);
    if (!tokens || !is_token_syntax_valid(tokens))
    {
        // ft_putstr_fd("Invalid Syntax\n", 2);
        env.stat_code = 258;
        ft_free_str_array(&tokens);
        return (NULL);
    }     
    if(tokens[get_2d_arr_len(tokens)][0] == '|')
    {
        input = join_pipes();
        if(input)
            get_command_for_pipe(toks, &tokens, input);
        else
        {
            ft_free_str_array(&tokens);
            free_env();
        }
    }
    return (tokens);    
}

int input_to_tokens(char *input)
{
    t_pars_tokens *pa_tkns;
    char    **tokens;

    // TOKEN SPLIT
    tokens = tokens_split(input);
    if(!tokens)
        return (EXIT_FAILURE);
    // PARCER
    
    pa_tkns  = parser(tokens);;
    ft_free_str_array(&tokens);
    // EXPANDER
    expander(pa_tkns);
    //EXECUTOR
    // print_strcut(pa_tkns);
   
	executor(pa_tkns);
    free_everything(pa_tkns);
	return (0);
}

