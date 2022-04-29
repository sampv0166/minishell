#include "../../includes/mini_shell.h"

extern t_env_var env;

void split_by_redirection(char **arr, char **tokens, t_split *split_info)
{
    if (!token_contains_quote(arr[split_info->i]))
    {
        while (arr[split_info->i][split_info->j])
        {
            split_info->len = 0;
            create_out_redirection_character(arr, split_info, tokens);   
            create_in_redirection_character(arr, split_info, tokens);
            create_pipe_redirection_character(arr, split_info, tokens);
            while(arr[split_info->i][split_info->j] && arr[split_info->i][split_info->j] != '>' && arr[split_info->i][split_info->j] != '<' && arr[split_info->i][split_info->j] != '|') 
            {
                split_info->len++;
                split_info->j++;
            }
            if(split_info->len > 0)
                tokens[split_info->k++] = ft_substr(arr[split_info->i], split_info->j - split_info->len, split_info->len);
        }
    }
    else
    {
        split_info->len = ft_strlen (arr[split_info->i]);
        tokens[split_info->k] = ft_strdup(arr[split_info->i]);
        split_info->k++;
    }
}

/*
    ! why this function ?  
    This function is used to further split the input if it contains pipes or redirections.
    !expected input : char *str    
    echo "hello world" >file|wc -l
    ! expected output : char **str
    str = ["echo", ""hello world"",">","file","|","wc", "-l"]  
*/

char **split_by_pipe_redir(char **arr, t_split *split_info)
{
    char **tokens;
    init_split_info(split_info);    
    tokens = (char **)ft_calloc(sizeof (char *), (get_len(arr) + 1));
    if (!tokens)
        return (NULL);
    while (arr[split_info->i])
    {
        split_info->j = 0;
        split_info->len = 0;
        split_by_redirection(arr, tokens, split_info);
        split_info->i++;
    }
    tokens[split_info->k] = NULL;
    free_2d_array(arr);
    return (tokens);
}
/*
    ! why this function ?  
    we cant use our normal split function to create tokens because , if we have a space
    in a string inside quotes, it will be splitted. for this reason we had to modify 
    split function.
    !expected input : char *str    
    echo "hello world">file|wc -l
    ! expected output : char **str
    str = ["echo", ""hello world"",">file|wc -l"]  
*/

char **split_to_tokens(char *str, t_split *split_info)
{
    init_split_info(split_info);
    char *temp ;
    split_info->arr = (char **)ft_calloc(sizeof (char *), (get_arr_len(str) + 1));
    if (!split_info->arr)
        return (NULL);    
    while (str[split_info->i] != '\0' && split_info->brk_flg)
    {
	    if (str[split_info->i] == ' ')
			split_info->i++;
		else if (str[split_info->i] && str[split_info->i] != ' ')
		{
            if(str[split_info->i] && str[split_info->i] == '\"')
                create_string_in_between_dbl_quotes(str ,split_info);
            else if(str[split_info->i] && str[split_info->i] == '\'')
                create_string_in_between_sngl_quotes(str ,split_info);
            else
            {
                while (str[split_info->i] && str[split_info->i] != ' ')
                    inrement_i_len(split_info);
                temp =  split_info->arr[split_info->array_index];
			    split_info->arr[split_info->array_index++] = ft_substr(str, split_info->i - split_info->len, split_info->len);
                split_info->len = 0; 
                if(str[split_info->i] == 0)
                    break ;  
            }
		}
    }
    split_info->arr[split_info->array_index] = NULL;
    return (split_info->arr);
}

char **join_toks(char **tok1, char **tok2)
{
    int len;
    len = get_2d_arr_len2(tok1) + get_2d_arr_len2(tok2);
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

int input_to_tokens(char *input)
{
    char **tokens;
    t_split *si;
    t_split *si2;
    si = malloc (sizeof (t_split));
    si2 = malloc (sizeof (t_split));
    if(!si || ! si2)
        return (EXIT_FAILURE);
    tokens = split_to_tokens(input, si);
    if(!tokens) 
        return(EXIT_FAILURE);
    //remove_empty_quotes();    
    tokens = split_by_pipe_redir(tokens, si2);
    //print_2d_array(tokens);
    //exit(0);

    if(!tokens) 
        return(EXIT_FAILURE);
    if (!is_token_syntax_valid(tokens))
    {
        printf("Invalid Syntax\n");
        return(258);
    }

    int d_len;
    d_len = get_2d_arr_len(tokens);
    if(tokens[d_len][0] == '|')
    {
        char *in;
        char *buf;
        in = NULL;
        buf = NULL;
        while(1)
        {
            buf = readline(">");
            in = ft_strjoin(in, buf);
            if(in[ft_strlen(in) - 1] == '|')
                continue;
            else
                break;    
        }
        t_split *s1;
        t_split *s2;
        char **toks;
        s1 = malloc (sizeof (t_split));
        s2 = malloc (sizeof (t_split));
        if(!s1 || !s2)
            return (EXIT_FAILURE);
        toks = split_to_tokens(in, s1);
        if(!toks) 
            return(EXIT_FAILURE);
        //remove_empty_quotes();    
        toks = split_by_pipe_redir(toks, s2);
        //print_2d_array(tokens);
        //exit(0);

        if(!toks) 
            return(EXIT_FAILURE);
        if (!is_token_syntax_valid(toks))
        {
            printf("Invalid Syntax\n");
            return(258);
        }
        tokens = join_toks(tokens, toks);
    }
    // print_2d_array(tokens);
    t_pars_tokens *pa_tkns;
    pa_tkns = parser(tokens);
    free_split_info(si, si2, tokens);

    // int y;
    // y = 0;
    // while (y < env.count)
    // {
    //     int j;
    //     j = 0;
    //     printf("\n struct = %d\n", y);
    //     printf("\n-------------cmd---------------------------\n");
    //     while (pa_tkns[y].cmd[j])
    //     {
    //         printf ("%s ",pa_tkns[y].cmd[j]);
    //         j++;
    //     }
    //     printf("\n-------------cmd_splitted---------------------------\n");
    //     j = 0;
    //     while (pa_tkns[y].cmd_splitted[j])
    //     {
    //         printf ("%s ",pa_tkns[y].cmd_splitted[j]);
    //         j++;
    //     }
    //     printf("\n-------------cmd_full---------------------------\n");
    //     printf ("%s ",pa_tkns[y].cmd_full);
    //     printf("\npipe = %d\n", pa_tkns[y].pipe);
    //     printf("\npipe_read_end = %d\n", pa_tkns[y].pipe_read_end);
    //     printf("\npipe_write_end = %d\n", pa_tkns[y].pipe_write_end);
    //     printf("\nis_out = %d\n", pa_tkns[y].is_out);
    //     printf("\nis_append = %d\n", pa_tkns[y].is_out_appnd);
    //     printf("\nis_in = %d\n", pa_tkns[y].is_in);
    //     printf("\nhere_doc = %d\n", pa_tkns[y].here_doc);
    //     printf("\nfd_out = %d\n", pa_tkns[y].fd_out);
    //     y++;
    //    // exit(0);
    // }
    //exit(0);
    executor (pa_tkns);
	return (EXIT_SUCCESS);
}
void print_2d_array(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        ft_putstr_fd(arr[i], 2);
         ft_putstr_fd("\n", 2);
        i++;
    }
}