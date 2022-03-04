#include "../../includes/mini_shell.h"


int get_pipe_len(char **tokens)
{
    int i;
    int len;

    i = 0;
    len = 0;

    while (tokens[i])
    {
        if(tokens[i][0] == '|')
            len++;
        i++;
    }
    return (len);
}

int get_count(char **tkns)
{
    int i;

    i = 0;

    while(tkns[i])
    {
        if(tkns[i][0] == '|')
            return (++i);
        i++;    
    }
    return (i);
}
t_pars_tokens *parser (char **tokens)
{
    int pipes_count;
    t_pars_tokens *pa_tkns;
    int i;
    
    i = 0;
    pipes_count = get_pipe_len(tokens) + 1;
    pa_tkns = malloc (sizeof (t_pars_tokens) * pipes_count + 1);
    pa_tkns[pipes_count + 1].cmd = NULL;
    pa_tkns[pipes_count + 1].cmd_splitted = NULL;
    int j;
    j = 0;
    while (pipes_count)
    {
        int len;
        char **arr;
        len = get_count(tokens);
        arr = malloc (sizeof (char *) * len + 1);

        char **arr1;
        len = get_count(tokens);

        arr1 = malloc (sizeof (char *) * len);
        char *str;    
        str = malloc (sizeof (char) * 1);
        len = 0;

        while(tokens[i])
        {
            // if (i > 0 && tokens[i - 1] && tokens[i - 1][0] == '|')
            // {
            //     str = ft_strjoin (str, tokens[i - 1]);
            // }
                
            if(tokens[i][0] == '|')
            {
                arr[len] = ft_strdup(tokens[i]);
                str = ft_strjoin (str, tokens[i]);
                len++;
                //if(tokens[i])
                i++;
                break ;
            }
            if(tokens[i][0] == '>' && tokens[i][1] == '>')
                pa_tkns[j].is_out_appnd = 1; 
            else if(tokens[i][0] == '>')
                pa_tkns[j].is_out = 1;
            if(tokens[i][0] == '<' && tokens[i][1] == '<')
                pa_tkns[j].here_doc = 1; 
            else if(tokens[i][0] == '<')
                pa_tkns[j].is_in = 1;              
            arr[len] = ft_strdup(tokens[i]);
            if(!(tokens[i][0] == '>' && tokens[i][1] == '>') && tokens[i][0] != '>' && !(tokens[i][0] == '<' && tokens[i][1] == '<') && tokens[i][0] != '<')
                arr1[len] = ft_strdup(tokens[i]);

            str = ft_strjoin (str, tokens[i]);
            len++;
            i++;
        }
        arr[len] = NULL;
        arr1[len] = NULL;
        pa_tkns[j].cmd_splitted = arr;
        pa_tkns[j].cmd = arr1;
        pa_tkns[j].cmd_full = str;
        pa_tkns[j].fd_in = STDIN_FILENO;
        pa_tkns[j].fd_out = STDOUT_FILENO;
        if(ft_strchr(str, '|'))
            pa_tkns[j].pipe = 1;
        // if(ft_strnstr(str,  "<<", 2))
        //     pa_tkns[j].here_doc = 1;     
        // else if (ft_strnstr(str,  "<", 1))
        //     pa_tkns[j].is_in = 1;  
        // if(ft_strnstr(str,  ">>", 2))
        //     pa_tkns[j].is_out_appnd = 1;              
        pipes_count--;
        j++;
    }
    return (pa_tkns);    
}
