#include "../../includes/mini_shell.h"

extern t_env_var env;

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

void init_parser_info(t_parser_info *pa_info, char **tokens)
{
    pa_info->pipes_count = 0;
    pa_info->i = 0;
    pa_info->k = 0;
    pa_info->len = 0;
    pa_info->arr = NULL;
    pa_info->arr1= NULL;
    pa_info->str = NULL;
    pa_info->j = 0;

    pa_info->pipes_count = get_pipe_len(tokens) + 1;
    env.count = pa_info->pipes_count;
}

void set_pipe_type(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
    pa_info->j = 0;
    while (pa_info->j < env.count)
    {
        if ((pa_tkns[pa_info->j].cmd_full && pa_tkns[pa_info->j].cmd_full[0] == '|') && (pa_tkns[pa_info->j].cmd_full[ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] == '|'))
        {
            pa_tkns[pa_info->j].pipe_read_end = 1;
            pa_tkns[pa_info->j].pipe_write_end = 1;
            pa_tkns[pa_info->j].pipe = 3;
        }
        else if (pa_tkns[pa_info->j].cmd_full[0] != '|' && pa_tkns[pa_info->j].cmd_full[ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] == '|')
        {
            pa_tkns[pa_info->j].pipe_read_end = 0;
            pa_tkns[pa_info->j].pipe_write_end = 1;
            pa_tkns[pa_info->j].pipe = 2;
        }
        else if (pa_tkns[pa_info->j].cmd_full[0] == '|' && pa_tkns[pa_info->j].cmd_full[ft_strlen(pa_tkns[pa_info->j].cmd_full) - 1] != '|')
        {
            pa_tkns[pa_info->j].pipe_read_end = 1;
            pa_tkns[pa_info->j].pipe_write_end = 0;
            pa_tkns[pa_info->j].pipe = 1;             
        }
        pa_info->j++;
    }
}

void allocate_cmd_memmory(t_parser_info *pa_info, char **tokens)
{        
    pa_info->len = get_count(tokens);
    pa_info->arr = malloc (sizeof (char *) *  ((pa_info->len) + 1)); // check_what
    pa_info->arr1 = malloc (sizeof (char *) *  ((pa_info->len) + 1)); // check_what  
    
    printf("\n%p\n",pa_info->arr);
    printf("\n%p\n",pa_info->arr1);
    //pa_info->str  = malloc (sizeof (char));
    pa_info->str = '\0';
    pa_info->len = 0;
}
void set_redirection_type(t_pars_tokens *pa_tkns, t_parser_info *pa_info, char **tokens)
{
    if(tokens[pa_info->i][0] == '>' && tokens[pa_info->i][1] == '>')
        pa_tkns[pa_info->j].is_out_appnd = 1; 
    else if(tokens[pa_info->i][0] == '>')
        pa_tkns[pa_info->j].is_out = 1;
    if(tokens[pa_info->i][0] == '<' && tokens[pa_info->i][1] == '<')
        pa_tkns[pa_info->j].here_doc = 1;
    else if(tokens[pa_info->i][0] == '<')
        pa_tkns[pa_info->j].is_in = 1; 
}

void set_pa_tokens(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
    pa_info->arr[pa_info->len] = NULL;
    pa_info->arr1[pa_info->len] = NULL;
    pa_tkns[pa_info->j].cmd_splitted = pa_info->arr;
    pa_tkns[pa_info->j].cmd =  pa_info->arr1;
    pa_tkns[pa_info->j].cmd_full =  pa_info->str;
    pa_tkns[pa_info->j].fd_in = STDIN_FILENO;
    pa_tkns[pa_info->j].fd_out = STDOUT_FILENO;
    pa_tkns[pa_info->j].is_in = 0;
    pa_tkns[pa_info->j].is_out = 0;
    pa_tkns[pa_info->j].is_out_appnd = 0;
    pa_tkns[pa_info->j].pipe = 0;
}

void deal_with_pipes(t_pars_tokens *pa_tkns, t_parser_info *pa_info, char **tokens)
{
    pa_info->arr[pa_info->len] = ft_strdup(tokens[pa_info->i]);
    pa_info->str = ft_strjoin (pa_info->str, tokens[pa_info->i]);
    pa_info->arr1[pa_info->len] = '\0';
    pa_info->len++;
    pa_info->i++;
    // pa_tkns[pa_info->j].fd_in = STDIN_FILENO;
    pa_tkns[pa_info->j].fd_out = STDOUT_FILENO;

    pa_tkns[pa_info->j].is_in = 0;
    pa_tkns[pa_info->j].is_out = 0;
    pa_tkns[pa_info->j].is_out_appnd = 0;
    pa_tkns[pa_info->j].pipe = 0;

}
void create_cmds(t_parser_info *pa_info, char **tokens)
{
    pa_info->arr[pa_info->len] = ft_strdup(tokens[pa_info->i]);
    if(!(tokens[pa_info->i][0] == '>' && tokens[pa_info->i][1] == '>') && tokens[pa_info->i][0] != '>' && !(tokens[pa_info->i][0] == '<' && tokens[pa_info->i][1] == '<') && tokens[pa_info->i][0] != '<')
            pa_info->arr1[pa_info->len] = ft_strdup(tokens[pa_info->i]);
    pa_info->str = ft_strjoin (pa_info->str, tokens[pa_info->i]);
    pa_info->len++;
    pa_info->i++;
    
}

void init_pa_tkns(t_pars_tokens *pa_tkns, t_parser_info *pa_info)
{
    int i;
    i = 0;
    
    while (i < pa_info->pipes_count)
    {
        pa_tkns[i].cmd = NULL;
        pa_tkns[i].cmd_full = NULL;
        pa_tkns[i].cmd_splitted = NULL;
        pa_tkns[i].pipe = 0;

        pa_tkns[i].is_in = 0;
        pa_tkns[i].is_out = 0;
        pa_tkns[i].is_out_appnd = 0;
        pa_tkns[i].fd_in = 0;

        pa_tkns[i].fd_out = 0;
        pa_tkns[i].here_doc = 0;

        pa_tkns[i].pipe_read_end = 0;
        pa_tkns[i].pipe_write_end= 0;
        i++;
    }
    env.pa_info = pa_info;
    env.pa_tkns = pa_tkns;
}

t_pars_tokens *parser (char **tokens)
{
    t_pars_tokens *pa_tkns;
    t_parser_info *pa_info;
    pa_info = malloc (sizeof (t_parser_info));
    init_parser_info(pa_info, tokens);
    pa_tkns = malloc (sizeof (t_pars_tokens) * (pa_info->pipes_count));
    init_pa_tkns(pa_tkns, pa_info);
    // pa_tkns[pa_info.pipes_count + 1].cmd = NULL;
    // pa_tkns[pa_info.pipes_count + 1].cmd_splitted = NULL;
    // pa_tkns[pa_info.pipes_count + 1].cmd_full = NULL;
    // pa_tkns[pa_info.pipes_count + 1].fd_in = STDIN_FILENO;
    // pa_tkns[pa_info.pipes_count + 1].fd_out = STDOUT_FILENO;
    // pa_tkns[pa_info.pipes_count + 1].pipe = 0;
    // pa_tkns[pa_info.pipes_count + 1].is_in = 0;
    // pa_tkns[pa_info.pipes_count + 1].is_out = 0;
    // pa_tkns[pa_info.pipes_count + 1].is_out_appnd = 0;
    // pa_tkns[pa_info.pipes_count + 1].here_doc = 0;

   // printf("\npipe-count = %d\n", pa_info.pipes_count);
    while (pa_info->j < pa_info->pipes_count)
    {
        allocate_cmd_memmory(pa_info, tokens);
        while(tokens[pa_info->i])
        {
            if (pa_info->i > 0 && tokens[pa_info->i - 1] && tokens[pa_info->i - 1][0] == '|')
            {
                //printf("%s", pa_info->str);
                //exit(0);
                pa_info->str = ft_strjoin(pa_info->str, tokens[pa_info->i - 1]);
            }
            if(tokens[pa_info->i][0] == '|')
            {
                deal_with_pipes(pa_tkns, pa_info, tokens);
                //print_2d_array(pa_info->arr1);
                break ;
            }
            set_redirection_type(pa_tkns, pa_info, tokens); 
            create_cmds(pa_info, tokens);
        }
        set_pa_tokens(pa_tkns, pa_info);
        pa_info->j++;
    }
    set_pipe_type(pa_tkns, pa_info);
    return (pa_tkns);    
}

            // if(ft_strchr(str, '|'))
        //     pa_tkns[j].pipe = 1;   
    //ls -la | wc -l | wc -l
    // printf("%ld", ft_strlen(pa_tkns[j].cmd_full));

    // k = pipes_count;

// int get_pipe_len(char **tokens)
// {
//     int i;
//     int len;

//     i = 0;
//     len = 0;

//     while (tokens[i])
//     {
//         if(tokens[i][0] == '|')
//             len++;
//         i++;
//     }
//     return (len);
// }

// int get_count(char **tkns)
// {
//     int i;

//     i = 0;

//     while(tkns[i])
//     {
//         if(tkns[i][0] == '|')
//             return (++i);
//         i++;    
//     }
//     return (i);
// }

// void init_pa_info(t_parser_info *pa_info, char **tokens, t_pars_tokens *pa_tkns)
// {
//     pa_info->pipes_count = 0;
//     pa_info->i = 0;
//     pa_info->k = 0;
//     pa_info->j = 0;
//     pa_info->pipes_count = get_pipe_len(tokens) + 1;
//     pa_tkns = malloc (sizeof (t_pars_tokens) * pa_info->pipes_count + 1);
// }
// t_pars_tokens *parser (char **tokens)
// {
//     t_pars_tokens *pa_tkns;
//     t_parser_info pa_info;
//     init_pa_info(&pa_info, tokens, pa_tkns);


    
    // pa_tkns[pa_info->pipes_count + 1].cmd = NULL;
    // pa_tkns[pa_info.pipes_count + 1].cmd_splitted = NULL;
    // pa_tkns[pa_info.pipes_count + 1].cmd_full = NULL;
    // pa_tkns[pa_info.pipes_count + 1].fd_in = STDIN_FILENO;
    // pa_tkns[pa_info.pipes_count + 1].fd_out = STDOUT_FILENO;
    // pa_tkns[pa_info.pipes_count + 1].pipe = 0;
    // pa_tkns[pa_info.pipes_count + 1].is_in = 0;
    // pa_tkns[pa_info.pipes_count + 1].is_out = 0;
    // pa_tkns[pa_info.pipes_count + 1].is_out_appnd = 0;
    // pa_tkns[pa_info.pipes_count + 1].here_doc = 0;
//     env.count = pa_info.pipes_count;
//     pa_info.k = pa_info.pipes_count;
    
//     while (pa_info.pipes_count)
//     {
//         int len;
//         char **arr;
//         len = get_count(tokens);
//         arr = malloc (sizeof (char *) * len + 1);
    
//         char **arr1;
//         len = get_count(tokens);

//         arr1 = malloc (sizeof (char *) * len);
//         char *str;    
//         str = malloc (sizeof (char) * 1);
//         len = 0;

//         while(tokens[pa_info.i])
//         {
//             if (pa_info.i > 0 && tokens[pa_info.i - 1] && tokens[pa_info.i - 1][0] == '|')
//             {
//                 str = ft_strjoin (str, tokens[pa_info.i - 1]);
//             }
//             if(tokens[pa_info.i][0] == '|')
//             {
//                 arr[len] = ft_strdup(tokens[pa_info.i]);
//                 str = ft_strjoin (str, tokens[pa_info.i]);
//                 len++;
//                 //if(tokens[i])
//                 pa_info.i++;
//                 break ;
//             }
//             if(tokens[pa_info.i][0] == '>' && tokens[pa_info.i][1] == '>')
//                 pa_tkns[pa_info.j].is_out_appnd = 1; 
//             else if(tokens[pa_info.i][0] == '>')
//                 pa_tkns[pa_info.j].is_out = 1;
//             if(tokens[pa_info.i][0] == '<' && tokens[pa_info.i][1] == '<')
//                 pa_tkns[pa_info.j].here_doc = 1;
//             else if(tokens[pa_info.i][0] == '<')
//                 pa_tkns[pa_info.j].is_in = 1;              
//             arr[len] = ft_strdup(tokens[pa_info.i]);
//             if(!(tokens[pa_info.i][0] == '>' && tokens[pa_info.i][1] == '>') && tokens[pa_info.i][0] != '>' && !(tokens[pa_info.i][0] == '<' && tokens[pa_info.i][1] == '<') && tokens[pa_info.i][0] != '<')
//                 arr1[len] = ft_strdup(tokens[pa_info.i]);

//             str = ft_strjoin (str, tokens[pa_info.i]);
//             len++;
//             pa_info.i++;
//         }
//         arr[len] = NULL;
//         arr1[len] = NULL;
//         pa_tkns[pa_info.j].cmd_splitted = arr;
//         pa_tkns[pa_info.j].cmd = arr1;
//         pa_tkns[pa_info.j].cmd_full = str;
//         pa_tkns[pa_info.j].fd_in = STDIN_FILENO;
//         pa_tkns[pa_info.j].fd_out = STDOUT_FILENO;
//         // if(ft_strchr(str, '|'))
//         //     pa_tkns[j].pipe = 1;       
//         pa_info.pipes_count--;
//         pa_info.j++;
//     }
//     pa_info.j = 0;
//     //ls -la | wc -l | wc -l
//     // printf("%ld", ft_strlen(pa_tkns[j].cmd_full));
   
//     while (pa_info.j < env.count)
//     {
//         if ((pa_tkns[pa_info.j].cmd_full && pa_tkns[pa_info.j].cmd_full[0] == '|') && (pa_tkns[pa_info.j].cmd_full[ft_strlen(pa_tkns[pa_info.j].cmd_full) - 1] == '|'))
//         {
//             pa_tkns[pa_info.j].pipe_read_end = 1;
//             pa_tkns[pa_info.j].pipe_write_end = 1;
//             pa_tkns[pa_info.j].pipe = 3;
//         }
//         else if (pa_tkns[pa_info.j].cmd_full[0] != '|' && pa_tkns[pa_info.j].cmd_full[ft_strlen(pa_tkns[pa_info.j].cmd_full) - 1] == '|')
//         {
//             pa_tkns[pa_info.j].pipe_read_end = 0;
//             pa_tkns[pa_info.j].pipe_write_end = 1;
//             pa_tkns[pa_info.j].pipe = 2;
//         }
//         else if (pa_tkns[pa_info.j].cmd_full[0] == '|' && pa_tkns[pa_info.j].cmd_full[ft_strlen(pa_tkns[pa_info.j].cmd_full) - 1] != '|')
//         {
//             pa_tkns[pa_info.j].pipe_read_end = 1;
//             pa_tkns[pa_info.j].pipe_write_end = 0;
//             pa_tkns[pa_info.j].pipe = 1;             
//         }
//         pa_info.j++;
//     }
//     return (pa_tkns);    
// }